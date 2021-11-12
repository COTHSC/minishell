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

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
    int fd[4][2];
    int i;
    int d;
    int *pids;
    int n;
     char *ls[] = {"ls", "-al", NULL};
     char *rev[] = {"rev", NULL};
     char *nl[] = {"nl", NULL};
     char *cat[] = {"cat", "-e", NULL};
    char **cmd[] = {ls, rev, nl, cat, NULL};

     n = 0;
     while (cmd[n])
         n++;

    pids = malloc(sizeof(int) * n );

    i = 0;
    while (i < n - 1)
    {
        if (pipe(fd[i]) < 0)
            return 1;
        i++;
    }
    int pid = 1;
    i = 0;
    while (i < n)
    {
        if (pid != 0)
        {
            pid = fork();
            pids[i] = pid;
        }
        i++;
    }
    i = 0;
    while (i < n - 1)
    {
            if (pids[i] == 0)
            {
                d = 0;
                while (d < n)
                {
                    if (d != i)
                        close(fd[d][0]);
                    if (d != i + 1)
                        close(fd[d][1]);
                    d++;
                }
                dup2(fd[i][0], 0);
                if (cmd[i+ 1] != NULL)
                    dup2(fd[i + 1][1], 1);
                execvp(cmd[i][0], cmd[i]);
                close(fd[i][0]);
                close(fd[i + 1][1]);
                return (0);
            }
        i++;
    }

    sleep(1);
   // wait(NULL);
    printf("I have come here\n");
    while(1)
    {;}
     

    return 0;
}
