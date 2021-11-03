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

int main(int argc, char **argv, char **env)
{
    int fd[2];
    int *fds;
    int i = 0;
    int pipes = 5;



    fds = calloc(sizeof(int *), 6);
    fd[0] = STDIN_FILENO;
    while (i < pipes)
    {
        pipe(fd);
        fds[i] = fork();
        if (fds[i] == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execlp("ping", "ping", "-c", "5", "google.com",  NULL);
        }
        i++;
    }
    if (fds[i] == 0 && i == pipes)
    {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execlp("grep", "grep", "rtt", NULL);
    }
    waitpid(fds[i], NULL, 0);



    return 0;
}
