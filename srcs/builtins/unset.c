/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:47:24 by calle             #+#    #+#             */
/*   Updated: 2021/12/02 16:13:12 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**delete_var(char **clean_env, char *var_to_del)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_str_list(strlen_list(g_env));
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

int	is_a_valid_name(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isanywordchar(var[i]))
			return (0);
		i++;
	}
	return (1);
}

int	delete_from_env(char *var_to_unset)
{
	char	**tmp;
	char	**name_value_pair;
	char	**clean_env;

	name_value_pair = split_to_name_value_pair(var_to_unset);
	clean_env = env_selector(1, NULL);
	if (match_var_name(clean_env, name_value_pair[0]))
	{
		tmp = delete_var(clean_env, name_value_pair[0]);
		if (!tmp)
			return (EXIT_FAILURE);
		free_str_list(g_env, strlen_list(g_env));
		g_env = tmp;
	}
	free_str_list(clean_env, strlen_list(clean_env));
	free_str_list(name_value_pair, strlen_list(name_value_pair));
	return (EXIT_SUCCESS);
}

int	check_and_delete_from_env(char **vars_to_unset)
{
	int		i;
	int		catch_error;
	int		catch_ret;

	i = 0;
	catch_error = 0;
	while (vars_to_unset[++i])
	{
		if (find_index_of_char(vars_to_unset[i], '=') != -1
			|| !has_valid_var_name(vars_to_unset[i]))
		{
			perror_not_a_valid_identifier(vars_to_unset[i], "unset");
			catch_error = 1;
			continue ;
		}
		catch_ret = delete_from_env(vars_to_unset[i]);
		if (catch_ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (catch_error);
}

int	ft_unset(int argc, char **argv)
{
	printf("var: %s\n", argv[1]);
	if (argc == 1)
		return (EXIT_SUCCESS);
	else if (is_option(argv[1]) && argv[1][1])
	{
		perror_invalid_option("unset", argv[1], NULL);
		print_usage_unset();
		return (2);
	}
	else
		return (check_and_delete_from_env(argv));
}
