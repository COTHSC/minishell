#include "./builtins.h"

enum e_builtins {e_cd, e_pwd};

int	select_builtin_test(int index, int argc, char **argv, char **env)
{
	static int	(*builtin_lookup[3])(int argc, char **args, char **env) = {ft_cd, ft_pwd, ft_exit};

	return (builtin_lookup[index](argc, argv, env));
}
