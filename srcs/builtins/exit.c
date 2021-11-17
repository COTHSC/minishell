#include "builtins.h"

int ft_exit(int argc, char **argv)
{
	int i;

	i = 0;
	(void)argc;
	(void)argv;
//	while (argv[i])
//	{
//		free(argv[i]);
//		i++;
//	}
//	free(argv);
	printf("exit \n");
	return (-14);
}
