#include "../builtins.h"

int ft_unset(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	printf("\n unset builtin.\n");
	return (EXIT_SUCCESS);
}
