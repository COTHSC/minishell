/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:43:01 by jescully          #+#    #+#             */
/*   Updated: 2020/12/02 10:53:04 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (((char *)s)[i] == ((char)c))
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}
