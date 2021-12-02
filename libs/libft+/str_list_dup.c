/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:03:16 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 19:06:41 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libftp.h"

char	**str_list_dup(char **src_list)
{
	char	**list_dup;
	int		i;

	i = 0;
	list_dup = calloc_str_list(strlen_list(src_list) + 1);
	if (!list_dup)
		return (NULL);
	while (src_list[i])
	{
		list_dup[i] = ft_strdup(src_list[i]);
		if (!list_dup[i])
			return (free_list_and_return_null(list_dup, i));
		i++;
	}
	return (list_dup);
}
