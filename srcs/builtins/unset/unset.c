#include "../builtins.h"

char	**delete_var(char **var_list, char *var_to_del)
{
	int	i;
	int j;
	char **tmp;
	int	nb_to_del;

	i = -1;
	j = 0;
	nb_to_del = 1;
	tmp = calloc_str_list(strlen_list(var_list) - nb_to_del);
	if (!tmp)
		return (NULL);
	while (var_list[++i])
	{
		if (var_is_matching(var_list[i], var_to_del))
			j--;
		else
		{
			tmp[j] = ft_strdup(var_list[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
	}
	return (tmp);
}

int	delete_element_from_env(char **env, char **vars_list)
{
	int	i;
	char **tmp;

	i = 1;
	while (vars_list[i])
	{
		if (match_in_var_list(env, vars_list[i]))
		{
			tmp = delete_var(env, vars_list[i]);
			if (!tmp)
				return (EXIT_FAILURE);
			free_str_list(env, strlen_list(env));
			env = str_list_dup(tmp);
			if (!tmp)
				return (EXIT_FAILURE);
			free_str_list(tmp, strlen_list(tmp));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_unset(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if (argc == 1)
		return (EXIT_SUCCESS);
	else
		return (delete_element_from_env(env, argv));
}
