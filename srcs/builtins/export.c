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


#include "builtins.h"

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
	q_env = calloc_str_list(strlen_list(env) + 1);
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

int	display_exported_vars( void )
{
	char	**exported_vars;
	char	**sorted_env;
	char	**prefixed_env;

	exported_vars = env_selector(1, "x");
	if (!exported_vars)
		return (EXIT_FAILURE);
	sorted_env = sort_str_list(exported_vars);
	if (!sorted_env)
	{
		free_str_list(exported_vars, strlen_list(exported_vars));
		return (EXIT_FAILURE);
	}
	prefixed_env = double_quoting_env_values(sorted_env);
	if (!prefixed_env)
	{
		free_str_list(exported_vars, strlen_list(exported_vars));
		free_str_list(sorted_env, strlen_list(sorted_env));
		return (EXIT_FAILURE);
	}
	print_str_list(prefixed_env, "declare -x ");
	if (exported_vars)
		free_str_list(exported_vars, strlen_list(exported_vars));
	if (sorted_env)
		free_str_list(sorted_env, strlen_list(sorted_env));
	if (prefixed_env)
		free_str_list(prefixed_env, strlen_list(prefixed_env));
	return (EXIT_SUCCESS);
}

int ft_export(int argc, char **argv)
{
	if (argc == 1)
		return (display_exported_vars());
	else if (is_option(argv[1]) && argv[1][1])	
	{
		perror_invalid_option("export", argv[1], NULL);
		print_usage_export();
		return (2);
	}
	else
		return (check_and_alter_env(argv + 1, "x"));
}
