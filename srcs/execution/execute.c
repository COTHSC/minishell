# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../includes/minishell.h"

int select_builtin_test(int index, int argc, char **argv);

void    free_command_block(char **command_block)
{
    int d;

    d = 0;
    while (command_block[d])
        free(command_block[d++]);
    free(command_block);
}

int     execute_builtin(char **command_block)
{
    int ret;

    ret = -1;
    if (command_block[0] && builtin_finder(command_block[0]) != -1)
        ret = select_builtin_test(builtin_finder(command_block[0]), strlen_list(command_block), command_block);
    return (ret);
}

int execute_binary(char **command_block)
{
    int     pid1;
    char    *path;
    int status;
    char **clean_env;

    pid1 = fork();
    if (pid1 == 0)
    {
        path = get_path(command_block);
        clean_env = ft_exported_vars('x');
        if ((execve(path, command_block, clean_env)) == -1)
        { 
            free(path);
            free_command_block(command_block);
            exit(EXIT_FAILURE);
        }
        free(clean_env);
        free (path);
        free_command_block(command_block);
    }
    waitpid(-1, &status, 0);
    if (WIFEXITED(status) ) 
        return (WEXITSTATUS(status));
   return (0); 
}

int close_unused_fds(int (*fd)[2], int current, int nb_cmds)
 {
     int idx;
     int current_read;
     int current_write;
     int ret;
 
     idx = 0;
     ret = 0;
     current_read = current;
     current_write = current + 1;
     while (idx < nb_cmds)
     {
         if (idx != current_read)
             ret = close(fd[idx][0]);
         if (idx != current_write)
             ret = close(fd[idx][1]);
         if (ret < 0)
             return (0);
         idx++;
     }
     return (1);
 }

int	ft_multipipes(void)
{
	int	(*fd)[2];
	int	counter = 0;
	int	*pids;
	int	nb_cmds;
	int	nb_builtins;
	int	nb_total;
	char 	*grep[] = {"grep", "home", NULL};
	char 	*wc[] = {"wc", "-l", NULL};
	char 	*env[] = {"env", NULL};
	char 	**cmds[] = {env, grep, wc, NULL};
	int	*is_builtin;
	

	while (cmds[counter])
		counter++;
	nb_total = counter;

	is_builtin = (int*)ft_calloc(sizeof(int), nb_total + 1);
	counter = 0;
	nb_builtins = 0;
	nb_cmds = 0;
	while (cmds[counter])
	{ 
		if (builtin_finder(cmds[counter][0]) != -1)
		{
			nb_builtins++;
			is_builtin[counter] = 1;
		}
		counter++;
	}

	counter = 0;
	while (cmds[counter])
	{ 
		if (builtin_finder(cmds[counter][0]) == -1)
		{
			nb_cmds++;
		}
		counter++;
	}
	
	counter = 0;

	fd = ft_calloc(sizeof(fd), nb_total + 1);
	while (counter <= nb_total)
	{
		pipe(fd[counter]);
		counter++;
	}	
	
	counter = 0;

	pids = malloc(sizeof(int) * 3);
	pids[0] = 1;
	pids[1] = 1;
	pids[2] = 1;
	while (counter < nb_total)
	{
		if (pids[counter] == 0)
			break;
		else
			pids[counter] = fork();
		counter++;
	}

	counter = 0;

	while (pids[counter] != 0 && counter < nb_cmds)
		counter++;

	if (counter != nb_cmds)
	{
		close_unused_fds(fd, counter, nb_total);
		dup2(fd[counter][0], STDIN_FILENO);
		if (cmds[counter + 1])
		{
			dup2(fd[counter + 1][1], STDOUT_FILENO);
		}
		execute_builtin(cmds[counter]);
		close(fd[counter][0]);
		close(fd[counter + 1][1]);
	}

	return 0;
}

int	is_child(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == 0)
			return (1);
		i++;
	}
	return (0);
}


int	ft_multipipes2(void)
{
		int (*fd)[2];
	int i;
	int *pids;
//	char *ls[] = {"ls", "-al", NULL};

	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char *env[] = {"env", NULL};
	char **cmd[] = {env, rev, nl, cat, NULL};

	i = 0;
	int n = 0;
	while (cmd[n])
		n++;
	fd = malloc(sizeof(*fd) * (n + 1));
	pids = malloc(sizeof(int) * n);
	while (i < n + 1)
	{
		if (pipe(fd[i]) < 0)
			return 1;
		i++;
	}
	int stdoutCopy = dup(1);

	i = 0;
	while (i < n)
	{
//		if (is_child(pids, i))
//			break;
		if (builtin_finder(cmd[i][0]) == -1)
			pids[i] = fork();
		else
			pids[i] = 1;
		if (pids[i] == 0)
			break;
		i++;
	}
//	i = 0;
/*	while (i < n)
	{
		if (pids[i] == 0)
			break;
		i++;
	}
*/
	if (i < n)
	{
		write(stdoutCopy, "am here\n", 8);
		if (!close_unused_fds(fd, i, n))
			exit(EXIT_FAILURE);
		dup2(fd[i][0], STDIN_FILENO);
		if (i != n - 1)
			dup2(fd[i + 1][1], STDOUT_FILENO);
		execvp(cmd[i][0], cmd[i]);
		close(fd[i][0]);
		close(fd[i + 1][1]);
		return (0);
	}
	i = 0;
	while (i < n)
	{
		if (builtin_finder(cmd[i][0]) != -1)
		{
			dup2(fd[i + 1][1], 1);
			execute_builtin(cmd[0]);
		//	write(STDOUT_FILENO, "am here\n", 8);
			dup2(stdoutCopy, 1);
		}
		i++;
	}
	close_unused_fds(fd, n + 1, n);
	pid_t wpid;
	int status;
	while ((wpid = wait(&status)) > 0);
	close(fd[n][1]);
	close(fd[n][0]);
	return (status);
}

int    execute(char **command_block)
{
    if (command_block[0])
    {/*
        if (builtin_finder(command_block[0]) != -1)
            return (execute_builtin(command_block));
        else
            return (execute_binary(command_block));
	    */
	 ft_multipipes2();
    }
    return (-1);
}
