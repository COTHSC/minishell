# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../includes/minishell.h"

char    *try_paths(char **paths, char *command)
{
    int     d;
    char    *path_bits;
    char    *path;

    d = -1;
    while (paths[++d])
    {
        path_bits = ft_strjoin(paths[d], "/");
        path = ft_strjoin(path_bits, command);
        free(path_bits);
        if (access(path, F_OK) == 0)
        {
            d = 0;
            while (paths[d])
                free(paths[d++]);
            free(paths);
            return (path);
        }
        free(path);
    }
    d = 0;
    while (paths[d])
        free(paths[d++]);
    free(paths);
    return (NULL);
}

int builtin_finder(char *name)
{
    int i;
    static char *builtin_lookup[7] = {"cd", "pwd", "exit", "export", "env", "unset", "echo"};

    i = 0;
    while (i < 7)
    {
        if (ft_strncmp(name, builtin_lookup[i], ft_strlen(name)) == 0)
            return (i);
        i++;
    }
    return (-1);
}

char    *get_path(char **command_block)
{
    char    **paths;
    int     d;
    char    *path;

    if (access(command_block[0], F_OK) == 0)
        return (command_block[0]);
    d = 0;
    paths = ft_split(getenv("PATH"), ':');
    path = try_paths(paths, command_block[0]);
    if (!path)
    {
        d = 0;
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command_block[0], 2);
        while (command_block[d])
            free(command_block[d++]);
        free(command_block);

        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    return (path);
}
