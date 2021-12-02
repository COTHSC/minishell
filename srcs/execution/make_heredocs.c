#include "../../includes/minishell.h"

int 	exec_heredoc(char *separator, int fds[2])
{
	char	*line;
	int		pid;
	int		test;
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
			if (!(test = get_next_line(STDIN_FILENO, &line)) && (line[0] == 0))
			{
			//	free(line);
				write(fds[1], pipe_buffer, size_to_write);
				reset_parent_tio_settings();
				ft_putstr_fd("minishell: warning: here-doc delimited by eof (wanted, dead or alive : ", STDOUT_FILENO);
				ft_putstr_fd(separator, STDOUT_FILENO);
				ft_putstr_fd(")", STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			//	free(separator);
				exit(0);
			}
			if (ft_strncmp(line, separator, ft_strlen(separator) + 1) || ft_strlen(line) == 0)
			{
				if (size_to_write + ft_strlen(line) + 2 > PIPE_BUF)
				{
					write(fds[1], pipe_buffer, size_to_write);
					free(line);
					close(fds[1]);
					exit(0);
				}
				size_to_write += ft_strlcpy(&pipe_buffer[size_to_write], line, ft_strlen(line) + 1);
				size_to_write++;
				pipe_buffer[size_to_write++] = '\n';
				free(line);
			}
			else
			{
				write(fds[1], pipe_buffer, size_to_write);
				free(line);
				close(fds[1]);
				exit(0);
			}
		}
	}
	wait(NULL);
	reset_parent_tio_settings();
	close(fds[1]);
	return (0);
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

char	*get_heredoc(char *s, int i)
{
	int		fd[2];
	char	*command;
	char	*test;
	char	*temp;

	if (!s[i + 1])
		return (s);
	command = ft_strndup(s, i);
	temp = make_heredocs(&s[i - 1], fd);
	test = ft_strjoin(command, temp);
	free_strs_return_null(3, command, temp, s);
	s = test;
	return (s);
}

char	*parse_line(char *s)
{
	int		i;
	int		quote;

	i = 1;
	while (s[i])
	{
		if (s[i - 1] == '<' && s[i] == '<')
			return (get_heredoc(s, i));
		quote = isquote(s[i - 1]);
		if (quote)
		{
			i = go_through_quote(s, i - 1, &quote);
			if (s[i])
				i++;
		}
		if (s[i])
			i++;
	}
	return (s);
}

char	**parse_block(char **cmd_block)
{
	int		i;
	char	*sep;
	int		fd[2];

	i = 0;
	if (!cmd_block[0] || !cmd_block[0][0])
		return (cmd_block);
	while (cmd_block[i])
	{
		cmd_block[i] = parse_line(cmd_block[i]);
		if (end_is_heredoc(cmd_block[i]))
		{
			sep = get_sep(cmd_block[i + 1]);
			exec_heredoc(sep, fd);
			cmd_block[i + 1] = replace_del(cmd_block[i + 1], sep, fd[0]);
			free(sep);
		}
		i++;
	}
	return (cmd_block);
}
