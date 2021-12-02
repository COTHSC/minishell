/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:17:03 by jescully          #+#    #+#             */
/*   Updated: 2021/12/02 15:17:04 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line(char *line, char buffer[PIPE_BUF], int fds[2], int size)
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
}

void	handle_del(char *line, char buffer[PIPE_BUF], int fds[2], int size)
{
	write(fds[1], buffer, size);
	free(line);
	close(fds[1]);
	exit(0);
}

int	wait_and_return(int fds[2])
{
	wait(NULL);
	reset_parent_tio_settings();
	close(fds[1]);
	return (0);
}

int	exec_heredoc(char *del, int fds[2])
{
	char	*s;
	int		pid;
	char	pipe_buffer[PIPE_BUF];
	int		size_to_write;

	ft_bzero(pipe_buffer, PIPE_BUF);
	pipe(fds);
	pid = fork();
	size_to_write = 0;
	if (pid == 0)
	{
		close(fds[0]);
		while (1)
		{
			reset_hd_tio_settings();
			ft_putstr_fd("> ", STDOUT_FILENO);
			if (!(get_next_line(STDIN_FILENO, &s)) && (s[0] == 0))
				handle_eof_sig(del, pipe_buffer, fds, size_to_write);
			if (ft_strncmp(s, del, ft_strlen(del) + 1) || ft_strlen(s) == 0)
				add_line(s, pipe_buffer, fds, size_to_write);
			else
				handle_del(s, pipe_buffer, fds, size_to_write);
		}
	}
	return (wait_and_return(fds));
}

char	*make_heredocs(char *seps, int fd[2])
{
	int		i;
	char	*separator;
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
				separator = get_sep(&seps[i]);
				exec_heredoc(separator, fd);
				free(separator);
				return (make_heredocs(&seps[i + 2], fd));
			}
		}
	}
	str_fd = ft_itoa(fd[0]);
	final_redir = ft_strjoin("<<", str_fd);
	free(str_fd);
	return (final_redir);
}
