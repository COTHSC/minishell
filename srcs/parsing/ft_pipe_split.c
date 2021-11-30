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

#include "../../includes/minishell.h"


static int	ft_countthewords_pipes(char const *s)
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
		if (s[i] == '|' && s[i + 1] != '|')
			cw++;
	}
	if (i == 0)
		return (0);
	if (s[0] != '|')
		cw++;
	if (s[i - 1] == '|')
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

int fill_word_pipes(char const *s, int lead)
{
	while (s[lead] != '|' && s[lead])
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

char	**ft_pipe_split(char const *s)
{
	char	**strs;
	int		lead;
	int		follow;
	int		row;
	int		quote;

	row = 0;
	lead = 0;
	quote = 0;
	strs = (char **)ft_calloc((ft_countthewords_pipes(s) + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	while (row < ft_countthewords_pipes(s))
	{
		while (s[lead] == '|' && !quote)
			lead++;
		quote = isquote(s[lead]);
		follow = lead;
		lead = go_through_quote(s, lead, &quote);
		lead = fill_word_pipes(s, lead);
		strs[row] = (char *)malloc(sizeof(char) * ((lead - follow + 1)));
		if (!strs)
			return (NULL);
		row = ftwtw(lead - follow, strs, row, (s + follow));
	}
	return (strs);
}
