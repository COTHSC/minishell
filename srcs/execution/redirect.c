# include "../../includes/minishell.h"
 # include <fcntl.h>
 # include <stdio.h>
 # include <fcntl.h>
 # include <unistd.h>
 # include <stdlib.h>
 # include <unistd.h>
 # include <string.h>
 # include <stdio.h>
 # include <sys/wait.h>
 # include <fcntl.h>

int     is_redirect(char c)
{
    if (c == '>')
        return (1);
    else if (c == '<')
        return (3);
    return (0);
}

void    check_fd(int fd, char *filename)
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
            ft_putstr_fd(filename, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
        }
        free(pwd);
        exit(1);
    }
    free(pwd);
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
	return (tmp);
}

int exec_dup(char *filenames, int redirect_type)
{
    int i;
    char *str;
    int fd;

    fd = 0;
    i = 0;
    while (filenames[i] && !is_redirect(filenames[i]))
        i++;
    str = ft_strdup(filenames);
    str[i] = 0;
    if (redirect_type == 2)
        fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0777);
    else if (redirect_type == 3)
        fd = open(str, O_RDONLY , 0777);
    else if (redirect_type == 1)
        fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    check_fd(fd, str);
    if (redirect_type < 3)
        dup2(fd, STDOUT_FILENO);
    else
        dup2(fd, STDIN_FILENO);
    if (!filenames[i])
    {
        close(fd);
        return 0;
    }
    else
    {
        redirect_type = 0;
        while ((filenames[i]) && is_redirect(filenames[i]))
            redirect_type += is_redirect(filenames[i++]);
        exec_dup(&filenames[i], redirect_type);
    }
    return (0);
}

char **make_dup(char **command_block, int index, int d, int redirect_type, int quiet)
{
    int i;
    char *filenames;
    char **cmd;

    filenames = malloc(sizeof(char *));
    cmd = command_block;
    i = index;
    while ((command_block[d][i]) && is_redirect(command_block[d][i]))
            redirect_type += is_redirect(command_block[d][i++]);
    if (i != index)
            command_block[d][index] = '\0';
    if (command_block[d][i])
    {
        filenames = ft_strdup(&command_block[d][i]);
        if (quiet == 0)
            exec_dup(filenames, redirect_type);
    }
    else 
    {
        make_dup(command_block, 0, d + 1, redirect_type, quiet);
        cmd = delete_str(command_block, d + 1);
    }
    return (cmd);
}

char    **ft_redirect(char **command_blocks, int quiet)
{
    int i;
    int d;
    char **command_block;

    command_block = str_list_dup(command_blocks);
    i = 0;
    while (command_block[i])
    {
        d = 0;
        while (command_block[i][d])
        {
            if (is_redirect(command_block[i][d]))
            {
                command_block = make_dup(command_block, d, i, 0, quiet);
                if (ft_strlen(command_block[i]) == 0)
                    command_block = delete_str(command_block, i);
                return (ft_redirect(command_block, quiet));
            }
            d++;
        }
        i++;
    }
    i = 0;
    if (!quiet)
        free(command_blocks);
    return (command_block);
}
