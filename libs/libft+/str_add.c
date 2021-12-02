/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:54:42 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 19:07:40 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftp.h"

char	**str_add(char **str_list, char *str_to_add)
{
	int		i;
	char	**dup_list;
	int		list_size;

	i = 0;
	list_size = strlen_list(str_list);
	dup_list = calloc_str_list(list_size + 2);
	if (!dup_list)
		return (NULL);
	while (i < list_size)
	{
		dup_list[i] = ft_strdup(str_list[i]);
		if (!dup_list[i])
			return (free_list_and_return_null(dup_list, i));
		i++;
	}
	dup_list[i] = ft_strdup(str_to_add);
	if (!dup_list[i])
		return (free_list_and_return_null(dup_list, i));
	return (dup_list);
}
