#include <stdio.h>
#include "../../libs/libft/libft.h"
#include "../../includes/minishell.h"

char	**g_env;

int	alter_env_var(char **clean_env, char *name, char *var_to_add, char *flag)
{
	int		i;
	char	**tmp;
	char	*flagged_var_to_add;

	i = index_matching_var_name(clean_env, name);
	flagged_var_to_add = ft_strjoin(flag, var_to_add);
	if (!flagged_var_to_add)
		return (EXIT_FAILURE);
	if (i == -1)
	{
		tmp = str_add(g_env, flagged_var_to_add);
		free(flagged_var_to_add);
		if (!tmp)
			return (EXIT_FAILURE);
		free_str_list(g_env, strlen_list(g_env));
		g_env = str_list_dup(tmp);
		free_str_list(tmp, strlen_list(tmp));
		if (!g_env)
			return (EXIT_FAILURE);
	}
	else
	{
		free(g_env[i]);
		g_env[i] = ft_strdup(flagged_var_to_add);
		if (!g_env[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	char	**name_value_pair;
	char	**clean_env;
	(void)argc;

	i = 1;
	g_env = str_list_dup(env);
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			clean_env = env_selector(1);
			name_value_pair = split_to_name_value_pair(argv[i]);
			alter_env_var(clean_env, name_value_pair[0], argv[i], "d");
			free_str_list(clean_env, strlen_list(clean_env));
			free_str_list(name_value_pair, strlen_list(name_value_pair));
		}
		i++;
	}
	print_str_list(g_env, NULL);
	return (0);
}
