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
		print_str_list(dup_env, NULL);
		printf("<<<<<<<<<< BEFORE UNSET\n\n");
		ft_unset(argc, argv, &dup_env);
		printf(">>>>>>>>>> AFTER UNSET\n\n");
		print_str_list(dup_env, NULL);
	}
	return (EXIT_SUCCESS);
}
