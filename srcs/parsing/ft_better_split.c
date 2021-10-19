/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_better_split.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jescully <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/10/19 10:59:38 by jescully		   #+#	  #+#			  */
/*	 Updated: 2021/10/19 14:25:08 by jescully		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "../../libs/libft+/libftp.h"

int isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	else 
		return (0);
}

static int	ft_countthewords(char const *s)
{
	int		i;
	int		cw;
	int		quotes;

	i = -1;
	cw = 0;
	quotes = 0;
	while (s[++i])
	{
		quotes = isquote(s[i]);
		while (quotes)
		{
			if (isquote(s[++i]) == quotes)
				quotes = 0;
		}
		if (ft_iswhitespace(s[i]) && !ft_iswhitespace(s[i + 1]))
			cw++;
	}
	if (i == 0)
		return (0);
	if (ft_iswhitespace(s[0]))
		cw++;
	if (!ft_iswhitespace(s[i - 1]))
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

int fill_word(char const *s, int lead)
{
	while (!ft_iswhitespace(s[lead]) && s[lead])
	{
		int quote = 0;
		{
			lead++;
			if (isquote(s[lead]))
				quote = isquote(s[lead]);
			while (quote)
			{
				lead++;
				if (isquote(s[lead]) == quote)
					quote = 0;
			}
		}
	}
	return (lead);
}

int go_through_quote(char const *s, int lead, int *quote)
{
	while (*quote)
	{
		lead++;
		if (isquote(s[lead]) == *quote)
			*quote = 0;
	}
	return (lead);
}

char	**ft_better_split(char const *s)
{
	char	**strs;
	int		lead;
	int		follow;
	int		row;
	int		quote;

	row = 0;
	lead = 0;
	quote = 0;
	strs = (char **)ft_calloc((ft_countthewords(s) + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	while (row < ft_countthewords(s))
	{
		while (ft_iswhitespace(s[lead]) && !quote)
			lead++;
		quote = isquote(s[lead]);
		follow = lead;
		lead = go_through_quote(s, lead, &quote);
		lead = fill_word(s, lead);
		strs[row] = (char *)malloc(sizeof(char) * ((lead - follow + 1)));
		if (!strs)
			return (NULL);
		row = ftwtw(lead - follow, strs, row, (s + follow));
	}
	return (strs);
}