/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:02:10 by jescully          #+#    #+#             */
/*   Updated: 2020/12/02 13:19:11 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischar(char o, char c)
{
	if (o == c)
		return (1);
	return (0);
}

static int	ft_countthewords(char const *s, char c)
{
	int		i;
	int		cw;

	i = 0;
	cw = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			cw++;
		i++;
	}
	if (i == 0)
		return (0);
	if (s[0] != c)
		cw++;
	if (s[i - 1] == c)
		cw--;
	return (cw);
}

static int	ftwtw(int len, char **strs, int row, const char *s)
{
	int		collumn;

	collumn = 0;
	while (collumn < len)
	{
		strs[row][collumn] = s[collumn];
		collumn++;
	}
	strs[row++][collumn] = '\0';
	return (row);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	**strs;
	int		lead;
	int		follow;
	int		row;

	row = 0;
	lead = 0;
	wc = ft_countthewords(s, c);
	strs = (char **)ft_calloc((wc + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	while (row < wc)
	{
		while (ft_ischar(s[lead], c))
			lead++;
		follow = lead;
		while (!ft_ischar(s[lead], c) && s[lead])
			lead++;
		strs[row] = (char *)malloc(sizeof(char) * ((lead - follow + 1)));
		if (!strs)
			return (NULL);
		row = ftwtw(lead - follow, strs, row, (s + follow));
	}
	return (strs);
}
