/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:34:14 by jean              #+#    #+#             */
/*   Updated: 2021/11/18 14:23:06 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*cs;

	if (!s)
		return (0);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int i;
	int cn;

	cn = (int)size;
	i = 0;
	if (cn == 0)
		return (ft_strlen(src));
	while (src[i] && i < cn - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < cn)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
