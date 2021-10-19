/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:23:26 by jescully          #+#    #+#             */
/*   Updated: 2020/12/02 13:02:29 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		c;
	size_t		d;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	c = 0;
	d = ft_strlen(s1);
	while (s1[i] && ft_ischarset(s1[i], set))
		i++;
	while (s1[i] && ft_ischarset(s1[d - 1], set))
		d--;
	d = d - i;
	str = (char *)malloc(sizeof(char) * (d + 1));
	if (!str)
		return (NULL);
	while (c < d)
		str[c++] = s1[i++];
	str[c] = '\0';
	return (str);
}
