# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../includes/minishell.h"

int select_builtin_test(int index, int argc, char **argv, char ***env);

void    free_command_block(char **command_block)
{
    int d;

    d = 0;
    while (command_block[d])
        free(command_block[d++]);
    free(command_block);
}

int     execute_builtin(char **command_block, char ***env)
{
    int ret;

    ret = -1;
    if (command_block[0] && builtin_finder(command_block[0]) != -1)
        ret = select_builtin_test(builtin_finder(command_block[0]), strlen_list(command_block), command_block, env);
    return (ret);
}

int execute_binary(char **command_block, char ***env)
{
    int     pid1;
    char    *path;
    int status;

    pid1 = fork();
    if (pid1 == 0)
    {
        path = get_path(command_block);
        if ((execve(path, command_block, *env)) == -1)
        {         
            free(path);
            free_command_block(command_block);
            exit(EXIT_FAILURE);
        }
        free (path);
        free_command_block(command_block);
    }
    waitpid(-1, &status, 0);
    if (WIFEXITED(status) ) 
        return (WEXITSTATUS(status));
   return (0); 
}

int    execute(char **command_block, char ***env)
{
    if (command_block[0])
    {
        if (builtin_finder(command_block[0]) != -1)
            return (execute_builtin(command_block, env));
        else
            return (execute_binary(command_block, env));
    }
    return (-1);
}
