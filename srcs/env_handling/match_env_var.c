/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:37:12 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 20:37:14 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_index_of_char(char *s, char c)
{
	char	*char_pos_ptr;

	char_pos_ptr = ft_strchr(s, c);
	if (char_pos_ptr)
		return (char_pos_ptr - s);
	else
		return (-1);
}

int	var_name_is_matching(char *var_to_compare, char *var_to_match)
{
	int		c_pos;
	char	*c_addr;
	int		max_len;
	int		sep;

	sep = '=';
	c_addr = ft_strchr(var_to_compare, sep);
	max_len = max_strlen(var_to_compare, var_to_match);
	if (!c_addr && ft_strncmp(var_to_compare, var_to_match, max_len) == 0)
		return (1);
	c_pos = c_addr - var_to_compare;
	if (c_pos == (long)ft_strlen(var_to_match)
		&& (ft_strnstr(var_to_compare, var_to_match, c_pos) - \
			var_to_compare == 0))
		return (1);
	return (0);
}

char	**match_var_name(char **var_list, char *var_to_match)
{
	int	i;

	i = 0;
	while (var_list[i])
	{
		if (var_name_is_matching(var_list[i], var_to_match))
			return (&var_list[i]);
		i++;
	}
	return (NULL);
}

int	index_matching_var_name(char **var_list, char *var_to_match)
{
	int	i;

	i = 0;
	while (var_list[i])
	{
		if (var_name_is_matching(var_list[i], var_to_match))
			return (i);
		i++;
	}
	return (-1);
}
