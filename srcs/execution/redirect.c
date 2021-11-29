# include "../../includes/minishell.h"

int     is_redirect(char c)
{
    if (c == '>')
        return (1);
    else if (c == '<')
        return (3);
    return (0);
}

int    check_fd(int fd, char *filename)
{
    char    *pwd;
    char    *temp;
    char    *temp1;
    
    temp = getenv("PWD");
    temp1 = ft_strjoin(temp, "/");
    pwd = ft_strjoin(temp1, filename);
    free(temp1);
    if (fd < 0)
    {
        if (access(pwd, F_OK) == 0)
        {
            ft_putstr_fd(filename, 2);
            ft_putstr_fd(": Permission denied\n", 2);
        }
        else
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(filename, 2);
            ft_putstr_fd(": No such file or directory\n", 2);

        }
        free(pwd);
        return (1);
    }
    free(pwd);
    return (0);
}

char	**delete_str(char **str_list, int index)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_str_list(strlen_list(str_list));
	if (!tmp)
		return (NULL);
	while (str_list[i])
	{
		if (i == index)
			j--;
		else
		{
			tmp[j] = ft_strdup(str_list[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
		i++;
	}
    free_str_list(str_list, strlen_list(str_list));
	return (tmp);
}

int open_file(int *fd, int redirect_type, char *file_name)
{
    int invalid_fd;

    if (redirect_type == 2)
        *fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
    else if (redirect_type == 3)
        *fd = open(file_name, O_RDONLY , 0777);
    else if (redirect_type == 1)
        *fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else if (redirect_type == 6)
        *fd = ft_atoi(file_name);
    invalid_fd = check_fd(*fd, file_name);
    if (invalid_fd)
        return (invalid_fd);
    return (0);
}

int exec_dup(int redirect_type, int fd)
{
    if (redirect_type < 3)
        dup2(fd, STDOUT_FILENO);
    else
        dup2(fd, STDIN_FILENO);
    return (0);
}

int filename_to_fd(char *filenames, int redirect_type, t_redir *redir)
{
    int i;
    char *str;
    int fd;
    static int index_fd;


    if (redir->fd[0] == -1)
        index_fd = 0;
    fd = 0;
    i = 0;
    while (filenames[i] && !is_redirect(filenames[i]))
        i++;
    str = ft_strdup(filenames);
    str[i] = 0;
    str = remove_quotes(str);
    if ((redir->es = open_file(&fd, redirect_type, str)))
    {
        free(str);
        return (1);
    }
    redir->fd[index_fd++] = fd;
    free(str);
    exec_dup(redirect_type, fd);
    if (filenames[i])
    {
        redirect_type = 0;
        while ((filenames[i]) && is_redirect(filenames[i]))
            redirect_type += is_redirect(filenames[i++]);
        filename_to_fd(&filenames[i], redirect_type, redir);
    }
    return (0);
}

char **get_filenames(t_redir *redir, int index, int d, int redirect_type)
{
    int i;
    char **cmd;

    cmd = redir->cmd;
    i = index;
    while ((redir->cmd[d][i]) && is_redirect(redir->cmd[d][i]))
    {
            redirect_type += is_redirect(redir->cmd[d][i++]);
            redir->cmd[d][index] = '\0';
    }
    if (redir->cmd[d][i])
            filename_to_fd(&redir->cmd[d][i], redirect_type, redir);
    else 
    {
        get_filenames(redir, 0, d + 1, redirect_type);
        cmd = delete_str(redir->cmd, d + 1);
    }
    return (cmd);
}

char    **ft_redirect(t_redir *redir)
{
    int i;
    int d;
    int quote;

    i = 0;
    while (redir->cmd[i])
    {
        d = 0;
        while (redir->cmd[i][d])
        {
            if (is_redirect(redir->cmd[i][d]))
            {
                if (!(redir->cmd = get_filenames(redir,  d, i, 0)))
                    return (NULL);
                if (ft_strlen(redir->cmd[i]) == 0)
                    redir->cmd = delete_str(redir->cmd, i);
                return (ft_redirect(redir));
            }
            if ((quote = isquote(redir->cmd[i][d])))
                d = go_through_quote(redir->cmd[i], d, &quote);
            d++;
        }
        i++;
    }
    return (redir->cmd);
}

char **get_filenames_no_redirect(char **command_block, int index, int d)
{
    int i;
    char **cmd;

    cmd = command_block;
    i = index;
    while ((command_block[d][i]) && is_redirect(command_block[d][i++]))
            command_block[d][index] = '\0';
    if (command_block[d][i])
        return (cmd);
    else 
    {
        get_filenames_no_redirect(command_block, 0, d + 1);
        cmd = delete_str(command_block, d + 1);
    }
    return (cmd);
}

char **get_command(char **cmd_block)
{
    int i;
    int d;
    int quote;

    i = 0;
    while (cmd_block[i])
    {
        d = 0;
        while (cmd_block[i][d])
        {
            if (is_redirect(cmd_block[i][d]))
            {
                if (!(cmd_block = get_filenames_no_redirect(cmd_block,  d, i)))
                    return (NULL);
                if (ft_strlen(cmd_block[i]) == 0)
                    cmd_block = delete_str(cmd_block, i);
                return (get_command(cmd_block));
            }
            if ((quote = isquote(cmd_block[i][d])))
                d = go_through_quote(cmd_block[i], d, &quote);
            d++;
        }
        return(cmd_block);
    }
    return (cmd_block);
}
