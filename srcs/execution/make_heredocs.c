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

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        close(fds[0]);
        while (1)
        {
            ft_putstr_fd("> ", 1);
            get_next_line(STDIN_FILENO, &line);
            if (ft_strncmp(line, separator, ft_strlen(separator) + 1) || ft_strlen(line) == 0)
            {
                ft_putstr_fd(line, fds[1]);
                ft_putstr_fd("\n", fds[1]);
                free(line);
            }
            else
            {
                free(line);
                close(fds[1]);
                exit(0);
            }
        }
    }
    wait(NULL);
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

char   *parse_line(char *command_line)
{
    int i;
    int fd[2];
    char *command;
    char *test;
    char *temp;

    i = 0;
    while (command_line[i + 1])
    {
        if (command_line[i] == '<' && command_line[i + 1] == '<')
        {
            if (!command_line[i + 2])
                return (command_line);
            command = ft_strndup(command_line, i);
            temp = make_heredocs(&command_line[i], fd);
            test = ft_strjoin(command, temp);
            free(command);
            free(temp);
            free(command_line);
            command_line = test;
            return (command_line);
        }
        i++;
    }
    return (command_line);
}

int     end_is_heredoc(char *s)
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

char    *replace_del(char *s, char *delimiter, int fd)
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

char    **parse_block(char **command_block)
{
    int i;
    char *sep;
    int fd[2];

    i = 0;
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