/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_through_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:04:43 by calle             #+#    #+#             */
/*   Updated: 2021/12/01 19:04:47 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libftp.h"

int	ft_test_through_str(char *str_to_check, int (*test)(int))
{
	int	i;

	if (!str_to_check)
		return (-1);
	i = 0;
	while (str_to_check[i])
	{
		if (test(str_to_check[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
