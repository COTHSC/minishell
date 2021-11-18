#include "builtins.h"

char	**delete_var(char **clean_env, char *var_to_del)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_str_list(strlen_list(g_env) + 1);
	if (!tmp)
		return (NULL);
	while (g_env[i])
	{
		if (var_name_is_matching(clean_env[i], var_to_del))
			j--;
		else
		{
			tmp[j] = ft_strdup(g_env[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
		i++;
	}
	return (tmp);
}

int	is_a_valid_identifier(char *var)
{
	int	i;

	i = 0;
	while (var[i])	
	{
		if (!ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}

int	delete_element_from_env(char **vars_to_unset)
{
	int		i;
	char	**tmp;
	char	**name_value_pair;
	char	**clean_env;

	i = 0;
	while (vars_to_unset[++i])
	{
		if (!is_a_valid_identifier(vars_to_unset[i]))
		{
			perror_not_a_valid_identifier(vars_to_unset[i], "unset");
			continue;
		}
		name_value_pair = split_to_name_value_pair(vars_to_unset[i]);
		clean_env = env_selector(1);
		if (match_var_name(clean_env, name_value_pair[0]))
		{
			tmp = delete_var(clean_env, name_value_pair[0]);
			if (!tmp)
				return (EXIT_FAILURE);
			free_str_list(g_env, strlen_list(g_env));
			g_env = str_list_dup(tmp);
			free_str_list(tmp, strlen_list(tmp));
			if (!g_env)
				return (EXIT_FAILURE);
		}
		free_str_list(clean_env, strlen_list(clean_env));
		free_str_list(name_value_pair, strlen_list(name_value_pair));
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(int argc, char **argv)
{
	if (argc == 1)
		return (EXIT_SUCCESS);
	else if (is_option(argv[1]) && argv[1][1])	
	{
		perror_invalid_option("unset", argv[1], NULL);
		print_usage_unset();
		return (2);
	}
	else
		return (delete_element_from_env(argv));
}
