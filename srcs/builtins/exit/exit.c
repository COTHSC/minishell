#include "../builtins.h"

int ft_exit(int argc, char **argv, char ***env)
{
	(void)argc;
	(void)argv;
	(void)env;

    printf("exit \n");
    exit(0);
	return (EXIT_SUCCESS);
}
