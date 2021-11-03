/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:15:47 by calle             #+#    #+#             */
/*   Updated: 2021/11/03 19:42:37 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	*free_and_return_str_list(char **str_list, int nbr_str_alloc)
{
	free_str_list(str_list, nbr_str_alloc);
	return (NULL);
}

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

char **env_selector(int position_selector)
{
	char	**selection;
	int		i;

	selection = calloc_str_list(strlen_list(g_env));
	i = 0;
	while (g_env[i])
	{
		selection[i] = ft_strdup(g_env[i] + position_selector);
		i++;
	}
	return (selection);
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

int	index_matching_var_name(char **var_list, char *var_to_match)
{
	int	i;
	int sep;

	i = 0;
	sep = '=';
	while (var_list[i])
	{
		if (var_name_is_matching(var_list[i], var_to_match))
			return (i);
		i++;
	}
	return (-1);
}

int	p_option_called(char *first_arg)
{
	if (ft_strncmp(first_arg, "-p", max_strlen(first_arg, "-p")) == 0)
		return (1);
	else
		return (0);
}

int	is_option(char *first_arg)
{
	return (*first_arg == '-');
}

int	var_already_exist(char **var_list, char *var)
{
	if (match_var_name(var_list, var))
		return (1);
	else
		return (0);
}

void	change_flag(char **var, char flag)
{
	*var[0] = flag;
}

int	change_value_in_env_var(char **clean_env, char *name, char *value)
{
	int		i;
	char	*tmp0;
	char	*tmp1;
	char	*tmp2;

	i = index_matching_var_name(clean_env, name);
	free(g_env[i]);
	tmp0 = ft_strjoin("x", name); 
	tmp1 = ft_strjoin(tmp0, "="); 
	if (!tmp1)
		return (EXIT_FAILURE);
	tmp2 = ft_strjoin(tmp1, value);
	if (!tmp2)
	{
		free(tmp1);
		return (EXIT_FAILURE);
	}
	g_env[i] = ft_strdup(tmp2);
	if (!g_env[i])
	{
		free(tmp1);
		free(tmp2);
		return (EXIT_FAILURE);
	}
	free(tmp0);
	free(tmp1);
	free(tmp2);
	return (EXIT_SUCCESS);
}

int	add_var_to_env(char *var_to_add)
{
	char	**tmp;
	char	*flagged_var_to_add;

	flagged_var_to_add = ft_strjoin("x", var_to_add);
	tmp = str_add(g_env, flagged_var_to_add);
	free(flagged_var_to_add);
	if (!tmp)
		return (EXIT_FAILURE);
	free_str_list(g_env, strlen_list(g_env));
	g_env = str_list_dup(tmp);
	free_str_list(tmp, strlen_list(tmp));
	if (!g_env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	do_export_on_env(char **new_vars)
{
	int		i;
	int		index_var_to_change;
	char	**clean_env;
	char	**name_value_pair;

	clean_env = env_selector(1);
	i = 1;
	while (new_vars[i])
	{
		name_value_pair = split_to_name_value_pair(new_vars[i]);
		if (var_already_exist(clean_env, name_value_pair[0]) && !var_has_value(new_vars[i]))
		{
			index_var_to_change = index_matching_var_name(clean_env, name_value_pair[0]);
			if (!var_is_exported(g_env[index_var_to_change]))
				change_flag(&g_env[index_var_to_change], 'x');
		}
		else if (var_already_exist(clean_env, name_value_pair[0]) && var_has_value(new_vars[i]))
			return (change_value_in_env_var(clean_env, name_value_pair[0], name_value_pair[1]));
		else
			return (add_var_to_env(new_vars[i]));
		free_str_list(name_value_pair, strlen_list(name_value_pair));
		i++;
	}
	free_str_list(clean_env, strlen_list(clean_env));
	return (EXIT_SUCCESS);
}

int ft_export(int argc, char **argv)
{
	if (argc == 1 || (argc == 2 && p_option_called(argv[1])))
		return (display_entire_env());
	if (argc == 2 && is_option(argv[1]) && !p_option_called(argv[1]))	
		return (EXIT_FAILURE);
	else
		return (do_export_on_env(argv));
}
