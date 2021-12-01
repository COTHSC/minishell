/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_and_return_null.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:38:18 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 18:38:19 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftp.h"

void	*free_list_and_return_null(char **str_list, int nbr_str_alloc)
{
	free_str_list(str_list, nbr_str_alloc);
	return (NULL);
}
