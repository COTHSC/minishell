/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:34:14 by jean              #+#    #+#             */
/*   Updated: 2021/11/29 16:22:36 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		size;
	char	*retstr;
	int		i;
	int		c;

	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	c = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	if (size == 0)
		return (NULL);
	if (!(retstr = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (s1[i])
	{
		retstr[i] = s1[i];
		i++;
	}
	while (s2[c])
		retstr[i++] = s2[c++];
	retstr[i] = '\0';
	free(s1);
	return (retstr);
}
