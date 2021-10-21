#include "../builtins.h"

int ft_exit(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	printf("\n exit builtin.\n");
	return (EXIT_SUCCESS);
}
