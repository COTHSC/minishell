#include "../builtins.h"

int main(int argc, char **argv, char **env)
{
	ft_echo(argc, argv, &env);
	return (EXIT_SUCCESS);
}
