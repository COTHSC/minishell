/*************************************************************************** */
/*                                                                           */
/*                                                       :::      ::::::::   */
/*  export.c                                           :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*  By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*  Created: 2021/11/04 13:27:09 by calle             #+#    #+#             */
/*  Updated: 2021/11/04 13:27:09 by calle            ###   ########.fr       */
/*                                                                           */
/*************************************************************************** */


#include "../builtins.h"

void	quote_and_cpy_val(int value_start, char *value, char **q_env, int i)
{
	q_env[i][value_start] = '"';
	ft_strlcpy(&q_env[i][value_start + 1], value, ft_strlen(value) + 1);
	q_env[i][value_start + ft_strlen(value) + 1] = '"';
}

char	**double_quoting_env_values(char **env)
{
	int		i;
	char	**q_env;
	int		dist;

	i = 0;
	q_env = calloc_str_list(strlen_list(env));
	if (!q_env)
		return (NULL);
	while (env[i])
	{
		if (var_has_value(env[i]))
		{
			q_env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 3));
			dist = extract_value(env[i]) - env[i];
			ft_strlcpy(q_env[i], env[i], dist + 1);
			quote_and_cpy_val(dist, extract_value(env[i]), q_env, i);
			q_env[i][ft_strlen(env[i]) + 2] = 0;
		}
		else
			q_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (q_env);
}

int	display_entire_env( void )
{
	char	**cleaned_env;
	char	**sorted_env;
	char	**prefixed_env;

	cleaned_env = env_selector(1);
	sorted_env = sort_str_list(cleaned_env);
	prefixed_env = double_quoting_env_values(sorted_env);
	print_str_list(prefixed_env, "declare -x ");
	if (cleaned_env)
		free_str_list(cleaned_env, strlen_list(cleaned_env));
	if (sorted_env)
		free_str_list(sorted_env, strlen_list(sorted_env));
	if (prefixed_env)
		free_str_list(prefixed_env, strlen_list(prefixed_env));
	return (EXIT_SUCCESS);
}

int	alter_env_var(char **clean_env, char *name, char *var_to_add)
{
	int		i;
	char	**tmp;
	char	*flagged_var_to_add;

	i = index_matching_var_name(clean_env, name);
	flagged_var_to_add = ft_strjoin("x", var_to_add);
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

int	do_export_on_env(char **new_vars)
{
	int		i;
	int		idx_var_to_alter;
	char	**clean_env;
	char	**name_value_pair;

	clean_env = env_selector(1);
	i = 1;
	while (new_vars[i])
	{
		name_value_pair = split_to_name_value_pair(new_vars[i]);
		if (var_already_exist(clean_env, name_value_pair[0]) && !var_has_value(new_vars[i]))
		{
			idx_var_to_alter = index_matching_var_name(clean_env, name_value_pair[0]);
			if (!var_is_exported(g_env[idx_var_to_alter]))
				change_flag(&g_env[idx_var_to_alter], 'x');
		}
		else
			alter_env_var(clean_env, name_value_pair[0], new_vars[i]);
		free_str_list(name_value_pair, strlen_list(name_value_pair));
		i++;
	}
	free_str_list(clean_env, strlen_list(clean_env));
	return (EXIT_SUCCESS);
}

int ft_export(int argc, char **argv)
{
	if (argc == 1 || (argc == 2 && option_is_called(argv[1], "-p")))
		return (display_entire_env());
	if (argc == 2 && is_option(argv[1]) && !option_is_called(argv[1], "-p"))	
		return (EXIT_FAILURE);
	else
		return (do_export_on_env(argv));
}
