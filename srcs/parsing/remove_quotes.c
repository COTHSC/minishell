/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:51:14 by jescully          #+#    #+#             */
/*   Updated: 2021/12/02 16:51:16 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quote(char *str, int i)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(str), sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i + 1);
	ft_strlcpy(&ret[i], &str[i + 1], ft_strlen(&str[i]) + 1);
	free(str);
	return (ret);
}

char	*remove_quotes(char *s)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s[i])
	{
		if (isquote(s[i]))
		{
			quotes = isquote(s[i]);
			s = remove_quote(s, i);
			while (isquote(s[i]) != quotes)
				i++;
			s = remove_quote(s, i);
			i--;
		}
		i++;
	}
	return (s);
}
