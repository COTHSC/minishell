#include "../../includes/minishell.h"

static void	perror_and_set_error(char *arg_error, char *builtin, int *error, int error_value)
{
	perror_not_a_valid_identifier(arg_error, builtin);
	*error = error_value;
}

int	check_and_alter_env(char **args, char *flag)
{
	int		i;
	int		idx_var_to_alter;
	char	**clean_env;
	char	**name_value_pair;
	int		ret_value;

	clean_env = env_selector(1, NULL);
	ret_value = 0;
	i = -1;
	while (args[++i])
	{
		name_value_pair = split_to_name_value_pair(args[i]);
		idx_var_to_alter = index_matching_var_name(clean_env, name_value_pair[0]);
		if (ft_strncmp(flag, "x", 1) == 0 && !has_valid_identifier(args[i]))
			perror_and_set_error(args[i], "export", &ret_value, 1);
		else if (idx_var_to_alter == -1
			|| (flag[0] == 'd' && !var_is_exported(g_env[idx_var_to_alter])))
			alter_env_var(clean_env, name_value_pair[0], args[i], flag);
		else if (flag[0] == 'x' && !var_has_value(args[i]))
			change_flag(&g_env[idx_var_to_alter], flag[0]);
		else
			alter_env_var(clean_env, name_value_pair[0], args[i], "x");
		free_str_list(name_value_pair, strlen_list(name_value_pair));
	}
	free_str_list(clean_env, strlen_list(clean_env));
	return (ret_value);
}
