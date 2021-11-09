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

#define NB_CMDS 126 
#define TRUE 1 
#define FALSE 0 

int	spawn_childs(int **pids)
{
	return (0);
}

int	close_unused_fds(int fd[NB_CMDS][2], int current, int nb_cmds)
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
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int main(int argc, char **argv, char **env)
{
    int fd[NB_CMDS][2];
    int i;
	int pids[NB_CMDS - 1];
    int x = 0;


    i = 0;
    while (i < NB_CMDS)
    {
        if (pipe(fd[i]) < 0)
            return 1;
        i++;
    }
	i = 0;
	while (i < NB_CMDS - 1)
	{
		if (is_child(pids, i))
			break;
		write(1, "SPAWNED\n", 8);
		pids[i] = fork();
		i++;
	}
	//pids[0] = fork();
	//if (pids[0] != 0)
	//	pids[1] = fork();
	i = 0;
	while (i < NB_CMDS - 1)
	{
		//printf("cmd-%d executing \n", i);
		if (pids[i] == 0)
		{
			printf("child-%d executing \n", i);
			if (!close_unused_fds(fd, i, NB_CMDS))
				exit(EXIT_FAILURE);
    	    int x;
			x = 0;
    	    read(fd[i][0], &x, sizeof(int));
    	    x += 5;
			printf("this is x %d\n", x);
    	    write(fd[i + 1][1], &x, sizeof(int));
    	    close(fd[i][0]);
    	    close(fd[i + 1][1]);
    	    return (0);
		}
		i++;
	}
	close_unused_fds(fd, NB_CMDS - 1, NB_CMDS);
    close(fd[NB_CMDS - 1][1]);
	wait(NULL);
    read(fd[NB_CMDS - 1][0], &x, sizeof(int));
    close(fd[NB_CMDS - 1][0]);
    printf("end x is %d\n", x);
    printf("done\n");
    return 0;
}
