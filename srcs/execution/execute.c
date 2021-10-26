/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:47:29 by jescully          #+#    #+#             */
/*   Updated: 2021/10/26 19:15:02 by jescully         ###   ########.fr       */
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

int select_builtin_test(int index, int argc, char **argv, char ***env);

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

int		strlen_list(char **str_list)
{
	int	i;

	i = 0;
	while (str_list[i])
		i++;
	return (i);
}

int    execute(char **command_block, char **env)
{
    int     d;
    int     pid1;
    char    *path;
    int status;

    d = 0;
    if (command_block[0] && builtin_finder(command_block[0]) != -1)
       return (select_builtin_test(builtin_finder(command_block[0]), strlen_list(command_block), command_block, &env));
    else
    {
        pid1 = fork();
        if (pid1 == 0)
        {
            path = get_path(command_block);
            if ((execve(path, command_block, env)) == -1)
            {         
                free(path);
                while (command_block[d])
                    free(command_block[d++]);
                free(command_block);
                exit(EXIT_FAILURE);
            }
            free (path);
            while (command_block[d])
                free(command_block[d++]);
            free(command_block);
        }
        waitpid(-1, &status, 0);
        if ( WIFEXITED(status) ) 
             return (WEXITSTATUS(status));
    }
    return (0);
}
