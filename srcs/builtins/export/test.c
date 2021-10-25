#include "builtins.h"
char	**str_list_dup(char **src_list);

int main(int argc, char **argv, char **env)
{
	char	**dup_env;

	if (argc == 1)
		return (EXIT_FAILURE);
	else
	{
		dup_env = str_list_dup(env);
		ft_export(argc, argv, &dup_env);
		print_str_list(dup_env, NULL);
	}
	return (EXIT_SUCCESS);
}
