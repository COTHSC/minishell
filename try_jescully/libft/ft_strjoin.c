/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:52:00 by jescully          #+#    #+#             */
/*   Updated: 2020/11/25 15:02:20 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*retstr;
	int		i;
	int		c;

	i = 0;
	c = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	retstr = (char *)malloc(sizeof(retstr) * (size + 1));
	if (retstr == NULL)
		return (NULL);
	while (s1[i])
	{
		retstr[i] = s1[i];
		i++;
	}
	while (s2[c])
	{
		retstr[i] = s2[c];
		i++;
		c++;
	}
	retstr[i] = '\0';
	return (retstr);
}
