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
	char    *path;
	char	**clean_env;

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

int	execute_child(int (*fd)[2], int i, int n, char **cmd)
{
	if (!close_unused_fds(fd, i, n))
		exit(EXIT_FAILURE);
	dup2(fd[i][0], STDIN_FILENO);
	if (i != n - 1)
		dup2(fd[i + 1][1], STDOUT_FILENO);
	// shoe in for redirections? they seem to take precedence over pipes...
	execute_binary(cmd);
	close(fd[i][0]);
	close(fd[i + 1][1]);
	return (0);
}

int	make_pipes(int (*fd)[2], int size)
{
	int i;

	i = 0;
	while (i < size + 1)
	{
		if (pipe(fd[i]) < 0)
			return 1;
		i++;
	}
	return (0);
}

int	nb_cmds(char ***cmd)
{
	int n;

	n = 0;
	while (cmd[n])
		n++;
	return (n);
}

int	ft_multipipes2(char ***cmd)
{
	int (*fd)[2];
	int i;
	int *pids;
	int status;
	int stdoutCopy = dup(1);
	int n = 0;
	pid_t wpid;

	while (cmd[n])
			n++;
	fd = malloc(sizeof(*fd) * (n + 1));
	pids = malloc(sizeof(int) * n);
	make_pipes(fd, n);
	i = 0;
	while (i < n)
	{
		if (builtin_finder(cmd[i][0]) == -1)
			pids[i] = fork();
		else
		{
			pids[i] = 1;
			if (i != n - 1)
				dup2(fd[i + 1][1], 1);
			execute_builtin(cmd[i]);
			if (i != n - 1)
				dup2(stdoutCopy, 1);
		}
		if (pids[i] == 0)
			execute_child(fd, i, n, cmd[i]);
		i++;
	}
	close_unused_fds(fd, n + 1, n);
	while ((wpid = wait(&status)) > 0);
	close(fd[n][1]);
	close(fd[n][0]);
	return (status);
}

int    execute(char ***command_block)
{
	if (command_block[0])
	{
		ft_multipipes2(command_block);
	}
	return (-1);
}
