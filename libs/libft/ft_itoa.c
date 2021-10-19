/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 09:45:20 by jescully          #+#    #+#             */
/*   Updated: 2020/12/05 21:34:27 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ilength(long long int number)
{
	int	i;

	i = 1;
	if (number < 0)
	{
		i++;
		number = -number;
	}
	while (number >= 10)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	nb;
	int				len;

	ret = (char *)malloc(sizeof(char) * (ilength(n) + 1));
	if (!ret)
		return (NULL);
	ret[ilength(n)] = '\0';
	nb = n;
	if (n < 0)
	{
		ret[0] = '-';
		nb = -n;
	}
	len = ilength(n) - 1;
	while (ilength(nb) != 1)
	{
		ret[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n >= 0)
		ret[0] = nb + '0';
	else
		ret[1] = nb + '0';
	return (ret);
}
