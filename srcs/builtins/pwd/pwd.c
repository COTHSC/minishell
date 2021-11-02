#include "../builtins.h"

int ft_pwd(int argc, char **argv, char ***env)
{
    char buf[PATH_MAX];

	(void)argv;
	(void)argc;
	(void)env;
   // if (argc != 1)
     //   return (-1);
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
