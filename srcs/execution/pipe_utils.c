#include "../../includes/minishell.h"

int	close_unused_fds(int (*fd)[2], int current, int nb_cmds)
{
	int	idx;
	int	current_read;
	int	current_write;
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

int	make_pipes(int (*fd)[2], int size)
{
	int	i;

	i = 0;
	if (size >= FD_SETSIZE / 2)
		return (1);
	while (i < size + 1)
	{
		if (pipe(fd[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_fds(int fd[100])
{
	int	i;

	i = 0;
	while (i < 100)
	{
		fd[i] = -1;
		i++;
	}
}

void	close_fds(int fd[100])
{
	int	i;

	i = 0;
	while (fd[i] != -1)
	{
		close(fd[i]);
		i++;
	}
}
