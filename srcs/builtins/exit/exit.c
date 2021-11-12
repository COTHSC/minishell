#include "../builtins.h"

int ft_exit(int argc, char **argv)
{
	int i;

	i = 0;
	(void)argc;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	printf("exit \n");
	exit(0);
	return (EXIT_SUCCESS);
}
