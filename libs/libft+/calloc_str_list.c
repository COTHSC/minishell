/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_str_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:29:24 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 18:37:37 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libftp.h"

char	**calloc_str_list(int size)
{
	char	**str_list;

	str_list = (char **)ft_calloc(size, sizeof(char *));
	return (str_list);
}
