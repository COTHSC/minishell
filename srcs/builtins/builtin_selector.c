#include "./builtins.h"

enum e_builtins {e_echo, e_cd, e_pwd, e_export, e_unset, e_env, e_exit};

int	select_builtin(int index, int argc, char **argv, char **env)
{
	static int	(*builtin_lookup[7])(int argc, char **args, char **env) = {
	ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};

	return (builtin_lookup[index](argc, argv, env));
}

int main(int argc, char **argv, char **env)
{
	select_builtin(e_exit, argc, argv, env);
	select_builtin(e_pwd, argc, argv, env);
	return (EXIT_SUCCESS);
}
