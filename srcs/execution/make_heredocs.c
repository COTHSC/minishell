/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:30:14 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 18:53:18 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_line(char *line, char buffer[PIPE_BUF], int fds[2], int size)
{
	if (size + ft_strlen(line) + 2 > PIPE_BUF)
	{
		write(fds[1], buffer, size);
		free(line);
		close(fds[1]);
		exit(0);
	}
	size += ft_strlcpy(&buffer[size], line, ft_strlen(line) + 1);
	size++;
	buffer[size++] = '\n';
	free(line);
	return (size);
}

void	handle_del(char *line, char buffer[PIPE_BUF], int fds[2], int size)
{
	write(fds[1], buffer, size);
	close(fds[1]);
	free(line);
	exit(0);
}

int	exec_heredoc(char *del, int fds[2])
{
	char	*s;
	int		pid;
	char	pipe_buffer[PIPE_BUF];
	int		size;

	ft_bzero(pipe_buffer, PIPE_BUF);
	pipe(fds);
	pid = fork();
	size = 0;
	if (pid == 0)
	{
		set_signal_handler_heredoc();
		close(fds[0]);
		while (1)
		{
			s = readline(">  ");
			if (!s)
				handle_eof_sig(del, pipe_buffer, fds, size);
			if (ft_strncmp(s, del, ft_strlen(del) + 1) || ft_strlen(s) == 0)
				size = add_line(s, pipe_buffer, fds, size);
			else
				handle_del(s, pipe_buffer, fds, size);
		}
	}
	return (wait_and_return(fds));
}

int	get_sep_and_exec(char *seps, int fd[2])
{
	char	*separator;

	separator = get_sep(seps);
	if (exec_heredoc(separator, fd))
	{
		free(separator);
		return (0);
	}
	free(separator);
	return (1);
}

char	*make_heredocs(char *seps, int fd[2])
{
	int		i;
	char	*final_redir;
	char	*str_fd;

	i = -1;
	while (seps[++i + 1])
	{
		if (seps[i] == '<' && seps[i + 1] == '<')
		{
			if (!seps[i + 2])
				return (seps);
			else
			{
				if (!get_sep_and_exec(&seps[i], fd))
					return (NULL);
				return (make_heredocs(&seps[i + 2], fd));
			}
		}
	}
	str_fd = ft_itoa(fd[0]);
	final_redir = ft_strjoin("<<", str_fd);
	free(str_fd);
	return (final_redir);
}
