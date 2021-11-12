#include <stdio.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
#include "../../libs/libft/libft.h"


int	spawn_childs(int **pids)
{
	return (0);
}

int	close_unused_fds(int (*fd)[2], int current, int nb_cmds)
{
	int	idx;
	int	current_read;
	int current_write;
	int	ret;

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

int main(int argc, char **argv, char **env)
{
	int (*fd)[2];
	int i;
	int *pids;
	char *ls[] = {"ls", "-al", NULL};
	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char **cmd[] = {ls, rev, nl, cat, NULL};

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
	i = 0;
	int stdoutCopy = dup(1); 
	dup2(fd[1][1], 1);

	write(STDOUT_FILENO, "How\n", 4);

	dup2(stdoutCopy, 1); 

	while (i < n)
	{
		if (is_child(pids, i))
			break;
		write(1, "SPAWNED\n", 8);
		pids[i] = fork();
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pids[i] == 0)
			break;
		i++;
	}

	if (i < n)
	{
		printf("child-%d executing \n", i);
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

	close_unused_fds(fd, n + 1, n);
	pid_t wpid;
	int status;
	while ((wpid = wait(&status)) > 0);
	close(fd[n][1]);
	close(fd[n][0]);

	printf("done\n");
	return 0;
}
