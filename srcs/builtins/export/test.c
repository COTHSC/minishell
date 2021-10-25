#include "../builtins.h"
int ft_export(int argc, char **argv, char **env);

int main(int argc, char **argv, char **env)
{
	if (argc == 1)
		return (EXIT_FAILURE);
	else
	{
		ft_export(argc, argv, env);
		//print_str_list(env, NULL);
	}
	return (EXIT_SUCCESS);
}
