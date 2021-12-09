/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:50:14 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 11:52:12 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*exp_rep(char *s, char *var_value, int offset, int i)
{
	int					d;
	char				*newstr;

	d = 0;
	if (offset < 0)
	{
		newstr = ft_strdup(&s[-offset]);
		while (d < (int)ft_strlen(var_value))
		{
			newstr[d] = var_value[d];
			d++;
		}
	}
	else
	{
		newstr = ft_calloc(ft_strlen(s) + offset + 1, sizeof(char));
		while (d <= (int)ft_strlen(var_value))
		{
			newstr[d] = var_value[d];
			d++;
		}
		ft_strlcpy(&newstr[ft_strlen(var_value)], &s[i], ft_strlen(s) - i + 1);
	}
	return (newstr);
}

char	*expand_vars(char *s, int status, int quote, int *index)
{
	int		i;
	char	*var_name;
	char	*var_value;
	int		offset;
	char	*newstr;

	i = 0;
	var_name = get_var_name(s, &i);
	if (!var_name[0])
	{
		free(var_name);
		if (is_done(s) || quote)
			return (ft_strjoin("$", s));
		else
			return (ft_strjoin("", s));
	}
	var_value = get_var_value(var_name, &offset, status);
	newstr = exp_rep(s, var_value, offset, i);
	if (var_value)
		free(var_value);
	free(var_name);
	if (newstr[0] == '$')
		*index = *index - 1;
	return (newstr);
}

char	*find_dollars(char *s, int status)
{
	int		i;
	char	*newend;
	char	*news;
	int		quote;

	i = -1;
	quote = 0;
	while (s && s[++i])
	{
		if (deal_with_quotes(s, &quote, &i) == -1)
			return (s);
		if (s[i] == '$')
		{
			s[i] = 0;
			newend = expand_vars(&s[i + 1], status, quote, &i);
			news = ft_strjoin(s, newend);
			free_strs_return_null(2, newend, s);
			s = news;
			if (!s[i])
				return (s);
		}
	}
	return (s);
}
