#include "./builtins.h"

enum e_builtins {e_cd, e_pwd};

int	select_builtin_test(int index, int argc, char **argv, char ***env)
{
	static int	(*builtin_lookup[4])(int argc, char **args, char ***env) = {ft_cd, ft_pwd, ft_exit, ft_export};

	return (builtin_lookup[index](argc, argv, env));
}
