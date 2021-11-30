#include "../../includes/minishell.h"

void	change_flag(char **var, char flag)
{
	*var[0] = flag;
}

//int var_is_shlvl(char *name)
//{
//    return (ft_strncmp(name, "SHLVL"))
//}
//
int	alter_env_var(char **clean_env, char *name, char *var_to_add, char *flag)
{
	int		i;
	char	**tmp_env;
	char	*flagged_var_to_add;

	i = index_matching_var_name(clean_env, name);
    if (name)
	flagged_var_to_add = ft_strjoin(flag, var_to_add);
	if (!flagged_var_to_add)
		return (EXIT_FAILURE);
	if (i == -1)
	{
		tmp_env = str_add(g_env, flagged_var_to_add);
		free(flagged_var_to_add);
		if (!tmp_env)
			return (EXIT_FAILURE);
		free_str_list(g_env, strlen_list(g_env));
		g_env = tmp_env;
		if (!g_env)
			return (EXIT_FAILURE);
	}
	else 
	{
		free(g_env[i]);
		g_env[i] = flagged_var_to_add;
		if (!g_env[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
