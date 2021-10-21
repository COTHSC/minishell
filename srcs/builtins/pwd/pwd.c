#include <unistd.h>
 #include <limits.h>
 #include "../../../libs/libft/libft.h"
 #include <errno.h>
 #include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv, char **env)
{
    char buf[PATH_MAX];

    if (!getcwd(buf, sizeof(buf)))
    {
        ft_putstr_fd("minishell: pwd: ", 1);
        perror(NULL);
        return (EXIT_FAILURE);
    }
    else
        printf("%s\n", buf);
    return (0);
}
