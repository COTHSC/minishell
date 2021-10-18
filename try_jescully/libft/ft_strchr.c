/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:05:59 by jescully          #+#    #+#             */
/*   Updated: 2021/01/29 11:05:17 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*cs;

	if (!s)
		return (NULL);
	cs = (char *)s;
	i = 0;
	while (s[i])
	{
		if (cs[i] == c)
			return (&cs[i]);
		i++;
	}
	if (cs[i] == c)
		return (&cs[i]);
	return (NULL);
}
