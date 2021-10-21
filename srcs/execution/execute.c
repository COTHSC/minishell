/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:47:29 by jescully          #+#    #+#             */
/*   Updated: 2021/10/19 15:57:41 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../libs/libft/libft.h"

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

char    *get_path(char **command)
{
    char    **paths;
    int     d;
    char    *path;

    if (access(command[0], F_OK) == 0)
        return (command[0]);
    d = 0;
    paths = ft_split(getenv("PATH"), ':');
    path = try_paths(paths, command[0]);
    if (!path)
    {
        d = 0;
        while (command[d])
            free(command[d++]);
        free(command);
        ft_putstr_fd(command[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(0);
    }
    return (path);
}

void    execute(char **command_block, char **env)
{
    int     d;
    char    *path;

    d = 0;
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
