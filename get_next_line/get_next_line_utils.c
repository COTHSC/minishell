/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:34:14 by jean              #+#    #+#             */
/*   Updated: 2021/12/01 19:30:04 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 100

int	not_a_ternary(int bytes, char *available_string)
{
	if (bytes + ft_strlen(available_string) == 0)
		return (0);
	else
		return (1);
}

int	get_str(char *bufstr, char **s, int fd, int *bytes)
{
	*bytes = read(fd, bufstr, BUFFER_SIZE);
	if (*bytes == -1)
	{
		free(bufstr);
		return (-1);
	}
	bufstr[*bytes] = '\0';
	*s = ft_strjoin2(*s, bufstr);
	return (0);
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
	retstr = (char *)malloc(sizeof(char) * (size + 1));
	if (!retstr)
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
