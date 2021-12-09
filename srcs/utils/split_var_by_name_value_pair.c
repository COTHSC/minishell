/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var_by_name_value_pair.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 21:00:38 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 21:00:40 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**split_till_char(char *s, char c)
{
	char	**tmp;
	char	*c_pos;

	c_pos = ft_strchr(s, c);
	if (!c_pos)
	{
		tmp = calloc_str_list(3);
		tmp[0] = ft_strdup(s);
		return (tmp);
	}
	else
	{
		tmp = calloc_str_list(3);
		tmp[0] = ft_calloc((c_pos - s + 1), 1);
		if (!tmp[0])
			return (NULL);
		ft_strlcpy(tmp[0], s, c_pos - s + 1);
		tmp[1] = ft_strdup(ft_strchr(s, c) + 1);
		if (!tmp[1])
		{
			free(tmp[0]);
			return (NULL);
		}
		return (tmp);
	}
}

char	**split_to_name_value_pair(char *var)
{
	return (split_till_char(var, '='));
}
