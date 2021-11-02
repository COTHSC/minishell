/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:15:47 by calle             #+#    #+#             */
/*   Updated: 2021/10/28 19:19:16 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	*free_and_return_str_list(char **str_list, int nbr_str_alloc)
{
	free_str_list(str_list, nbr_str_alloc);
	return (NULL);
}

char	**double_quoting_env_value(char **src)
{
	int		i;
	char	*equal_pos;
	char	**dest;
	int		dist;

	i = 0;
	dest = calloc_str_list(strlen_list(src));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		equal_pos = ft_strchr(src[i], '=');
		if (equal_pos)
		{
			dest[i] = malloc(sizeof(char) * (ft_strlen(src[i]) + 3));
			dist = equal_pos - src[i];
			ft_strlcpy(dest[i], src[i], dist + 2);
			dest[i][dist + 1] = '"';
			ft_strlcpy(&dest[i][dist + 2], &src[i][dist + 1], ft_strlen(&src[i][dist]));
			dest[i][ft_strlen(src[i]) + 1] = '"';
			dest[i][ft_strlen(src[i]) + 2] = 0;
		}
		i++;
	}
	return (dest);
}

int	display_entire_env_vars(char **env)
{
	char	**temp1;
	char	**temp2;

	temp1 = sort_str_list(env);
	temp2 = double_quoting_env_value(temp1);
	print_str_list(temp2, "declare -x ");
	if (temp1)
		free_str_list(temp1, strlen_list(temp1));
	if (temp2)
		free_str_list(temp2, strlen_list(temp2));
	return (EXIT_SUCCESS);
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
	if (match_in_var_list(var_list, var))
		return (1);
	else
		return (0);
}

int	var_has_value(char **var_list, char *var)
{
	if (extract_value(match_in_var_list(var_list, var)))
		return (1);
	else
		return (0);
}

int	var_is_exported(char *var)
{
	return (var[0] == 'x');
}

void	change_flag(char **var, char flag)
{
	*var[0] = flag;
}

char	*extract_value(char *var)
{
	char	sep;

	sep = '=';
	return (ft_strchr(var, sep));
}

char	*change_var_value(char **var, char *new_value)
{
	
	
}

int	add_var_to_env(char ***env, char *var_to_add)
{
	char	**tmp;
	char	*flagged_var_to_add;

	flagged_var_to_add = ft_str_join("x", var_to_add);
	tmp = str_add(*env, flagged_var_to_add);
	free(flagged_var_to_add);
	if (!tmp)
		return (EXIT_FAILURE);
	free_str_list(*env, strlen_list(*env));
	*env = str_list_dup(tmp);
	free_str_list(tmp, strlen_list(tmp));
	return (EXIT_SUCCESS);
}

int	do_export(char **new_vars, char ***env)
{
	int		i;
	char	**var_to_change;

	i = 1;
	while (new_vars[i])
	{
		if (var_already_exist(&*env[1], &new_vars[i][1]) && !var_has_value(new_vars[i]))
		{
			var_to_change = match_in_var_list(*env, new_vars[i]);
			if (!var_is_exported(*var_to_change))
				change_flag(var_to_change, 'x');
		}
		else if (var_already_exist(&*env[1], &new_vars[i][1]) && var_has_value(new_vars[i]))
		{
			//replace all var=name in the env list with a x flag
		}
		else
			add_var_to_env(env, new_vars[i]);
	}
	return (EXIT_SUCCESS);
}

int ft_export(int argc, char **argv, char ***env)
{
	if (argc == 1 || (argc == 2 && p_option_called(argv[1])))
		return (display_entire_env_vars(*env));
	if (argc == 2 && is_option(argv[1]) && !p_option_called(argv[1]))	
		return (EXIT_FAILURE);
	else if
		return (do_export(argv, env));
}
