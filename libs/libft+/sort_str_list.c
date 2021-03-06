/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_str_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:57:54 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 18:57:56 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libftp.h"

static void	fill_dest_with_unique(char **dest, char **src, int dest_pos)
{
	int	i;

	i = 0;
	while (!dest[dest_pos])
	{
		if (is_not_in_str_list(dest, src[i]))
			dest[dest_pos] = ft_strdup(src[i]);
		i++;
	}
}

char	**sort_str_list(char **list)
{
	char	**t;
	int		i;
	int		j;

	j = 0;
	t = calloc_str_list(strlen_list(list) + 1);
	while (t && j < strlen_list(list))
	{
		i = 0;
		while (list[i])
		{
			fill_dest_with_unique(t, list, j);
			if (t[j]
				&& ft_strncmp(t[j], list[i], max_strlen(t[j], list[i])) > 0
				&& is_not_in_str_list(t, list[i]))
			{
				free(t[j]);
				t[j] = ft_strdup(list[i]);
			}
			i++;
		}
		j++;
	}
	return (t);
}
