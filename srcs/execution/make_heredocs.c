# include "../../includes/minishell.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *get_sep(char *sep_str)
{
	char **seps;
	char *sep;

	seps = ft_split(sep_str, '<');
	sep = ft_strdup(seps[0]);
	free_str_list(seps, strlen_list(seps));
	return (sep);
}

int exec_heredoc(char *separator, int fds[2])
{
	char *line;
	int pid;
	int test;
	char pipe_buffer[PIPE_BUF];
	int size_to_write;

	ft_bzero(pipe_buffer, PIPE_BUF);
	pipe(fds);
	pid = fork();
	size_to_write = 0;
	if (pid == 0)
	{
		close(fds[0]);
		while (1)
		{	 
			int test;
			reset_hd_tio_settings();
			ft_putstr_fd("> ", STDOUT_FILENO);
			if (!(test = get_next_line(STDIN_FILENO, &line)) && (line[0] == 0  || (int)line[0] == 3))
			{
				write(fds[1], pipe_buffer, size_to_write);
				reset_parent_tio_settings();
				ft_putstr_fd("minishell: warning: here-doc delimited by eof (wanted, dead or alive : ", STDOUT_FILENO);
				ft_putstr_fd(separator, STDOUT_FILENO);
				ft_putstr_fd(")", STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
				free(line);

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
	wait(&test);
	reset_parent_tio_settings();
	close(fds[1]);
	return (0);
}

char *make_heredocs(char *seps, int fd[2])
{
	int i = 0;
	char *separator;
	char *final_redir;
	char *str_fd;

	while (seps[i + 1])
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
		i++;
	}
	str_fd = ft_itoa(fd[0]);
	final_redir = ft_strjoin("<<", str_fd);
	free(str_fd);
	return (final_redir);
}

char   *parse_line(char *s)
{
	int i;
	int fd[2];
	char *command;
	char *test;
	char *temp;
	int quote;

	i = 1;
	while (s[i])
	{
		if (s[i - 1] == '<' && s[i] == '<')
		{
			if (!s[i + 1])
				return (s);
			command = ft_strndup(s, i);
			temp = make_heredocs(&s[i - 1], fd);
			test = ft_strjoin(command, temp);
			free(command);
			free(temp);
			free(s);
			s = test;
			return (s);
		}
		if ((quote = isquote(s[i - 1])))
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

int		end_is_heredoc(char *s)
{
	int str_len;

	str_len = ft_strlen(s);
	if (!s)
		return (0);
	else if (str_len < 2)
		return (0);
	else if (s[str_len - 1] == '<' && s[str_len - 2] == '<')
		return (1);
	else
		return (0);
}

char	*replace_del(char *s, char *delimiter, int fd)
{
	char *fd_str;
	char *temp;
	char *news;

	fd_str = ft_itoa(fd);
	temp = ft_strdup(&s[ft_strlen(delimiter)]);
	news = ft_strjoin(fd_str, temp);
	free(temp);
	free(s);
	s = news;
	free(fd_str);
	return (s);
}

char	**parse_block(char **command_block)
{
	int i;
	char *sep;
	int fd[2];

	i = 0;
	if (!command_block[0] || !command_block[0][0])
		return (command_block);	
	while (command_block[i])
	{
		command_block[i] = parse_line(command_block[i]);
		if (end_is_heredoc(command_block[i]))
		{
			sep = get_sep(command_block[i + 1]);
			exec_heredoc(sep, fd);
			command_block[i + 1] = replace_del(command_block[i + 1], sep, fd[0]);
			free(sep);
		}
		i++;
	}
	return (command_block);
}
