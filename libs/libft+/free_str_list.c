/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:27:10 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 18:37:45 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libftp.h"

void	free_str_list(char **str_list, int size_to_free)
{
	int	i;

	i = 0;
	while (i < size_to_free && str_list[i])
	{
		free(str_list[i]);
		i++;
	}
	free(str_list);
}
