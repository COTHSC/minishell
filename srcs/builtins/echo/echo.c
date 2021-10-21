#include "../builtins.h"

int ft_echo(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	printf("\n echo builtin.\n");
	return (EXIT_SUCCESS);
}
