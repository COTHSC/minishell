/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_not_in_str_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:55:10 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 18:55:12 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libftp.h"

int	is_not_in_str_list(char **str_list, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str_list[i])
	{
		if (!ft_strncmp(str_list[i], str, max_strlen(str_list[i], str)))
			return (0);
		i++;
	}
	return (1);
}
