/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:30:14 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 18:26:43 by jescully         ###   ########.fr       */
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

int	wait_and_return(int fds[2])
{
	int	status;

	status = wait_and_get_status();
	setcher(status);
	close(fds[1]);
	reset_parent_tio_settings();
	signal_handler_settings();
	return (status);
}

static void	handle_sig_hd(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(130);
	}
}

void	set_signal_handler_heredoc(void)
{
	static struct sigaction	sa_hd;

	sa_hd.sa_sigaction = &handle_sig_hd;
	sa_hd.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa_hd, NULL);
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
		reset_hd_tio_settings();
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
	else
		signal(SIGINT, SIG_IGN);
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
				if (exec_heredoc(separator, fd))
				{
					free(separator);
					return (NULL);
				}
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
