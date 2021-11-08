#include "../builtins.h"

int ft_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;

    printf("exit \n");
    exit(0);
	return (EXIT_SUCCESS);
}
