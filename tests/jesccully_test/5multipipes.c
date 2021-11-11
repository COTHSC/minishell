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
    int fd[3][2];
    int i;
    int pid1;
    int pid2;

    i = 0;
    while (i < 3)
    {
        if (pipe(fd[i]) < 0)
            return 1;
        i++;
    }
    pid1 = fork();
    pid2 = fork();

    if (pid1 == 0)
    {
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][1]);
        close(fd[2][0]);
        int x;
        x = 0;
        read(fd[0][0], &x, sizeof(int));
        x += 5;
    printf("this is x %d\n", x);
        write(fd[1][1], &x, sizeof(int));
        close(fd[0][0]);
        close(fd[1][1]);
        return (0);
    }

    if (pid2 == 0)
    {
        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[0][1]);
        close(fd[2][0]);
        int x;
        read(fd[1][0], &x, sizeof(int));
        x += 5;
    printf("this is x %d\n", x);
        write(fd[2][1], &x, sizeof(int));
        close(fd[1][0]);
        close(fd[2][1]);
        return (0);
    }

    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][1]);
    close(fd[2][1]);
    close(fd[2][1]);

    int x;
    read(fd[2][0], &x, sizeof(int));
    close(fd[2][0]);

    printf("this is x %d\n", x);
    while (1)
    {;}
    return 0;
}
