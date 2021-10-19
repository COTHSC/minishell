/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:59:38 by jescully          #+#    #+#             */
/*   Updated: 2021/10/19 13:23:13 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"

static int	ft_ischar(char o, char c)
{
	if (o == c)
		return (1);
	return (0);
}

int isquote(char c)
{
    if (c == '\'')
        return (1);
    else if (c == '"')
        return (2);
    else 
        return (0);
}

static int	ft_countthewords(char const *s, char c)
{
	int		i;
	int		cw;
    int     quotes;

	i = 0;
	cw = 0;
    quotes = 0;
	while (s[i])
	{
        if (isquote(s[i]))
        {
            quotes = isquote(s[i]);
            while (quotes)
            {
                i++;
                if (isquote(s[i]) == quotes)
                    quotes = 0;
            }
        }
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

char	**ft_better_split(char const *s, char c)
{
	int		wc;
	char	**strs;
	int		lead;
	int		follow;
	int		row;
	int		quote;

	row = 0;
	lead = 0;
	quote = 0;
	wc = ft_countthewords(s, c);
	strs = (char **)ft_calloc((wc + 1), sizeof(char *));
	if (!strs)
		return (NULL);
    while (row < wc)
    {
        while (ft_ischar(s[lead], c) && !quote)
            lead++;
        if (isquote(s[lead]))
        {
            quote = isquote(s[lead]);
        }
          
        follow = lead;
        while (quote)
        {
            lead++;
            if (isquote(s[lead]) == quote)
                quote = 0;
        }
        while (!ft_ischar(s[lead], c) && s[lead])
        {
            while (quote)
            {
                lead++;
                if (isquote(s[lead]) == quote)
                    quote = 0;
            }
            lead++;
            if (isquote(s[lead]))
                quote = isquote(s[lead]);
        }
        strs[row] = (char *)malloc(sizeof(char) * ((lead - follow + 1)));
        if (!strs)
            return (NULL);
        row = ftwtw(lead - follow, strs, row, (s + follow));
    }
    return (strs);
}
