/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:47:29 by jescully          #+#    #+#             */
/*   Updated: 2021/10/25 18:50:03 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../includes/minishell.h"

 int select_builtin_test(int index, int argc, char **argv, char **env);
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
    static char *builtin_lookup[3] = {"cd", "pwd", "exit"};

    i = 0;
    while (i < 3)
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
        ft_putstr_fd(command_block[0], 2);
        while (command_block[d])
            free(command_block[d++]);
        free(command_block);
        ft_putstr_fd(": command not found\n", 2);
        exit(0);
    }
    return (path);
}

int    execute(char **command_block, char **env)
{
    int     d;
    int     pid1;
    char    *path;

    d = 0;
    if (builtin_finder(command_block[0]) != -1)
       return (select_builtin_test(builtin_finder(command_block[0]), 1 , command_block, env));
    else
    {
        pid1 = fork();
        if (pid1 == 0)
        {
            path = get_path(command_block);
            if (execve(path, command_block, env) == -1)
            {         
                free(path);
                while (command_block[d])
                    free(command_block[d++]);
                free(command_block);
                exit(0);
            }
            free (path);
        }
    }
    return (1);
}
