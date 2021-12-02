/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:50:33 by jescully          #+#    #+#             */
/*   Updated: 2021/12/02 17:06:26 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_done(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!isquote(s[i]) && s[i] != '/' && s[i] != '%' && s[i] != '\\')
			return (0);
		i++;
	}
	return (1);
}

char	*get_var_name(char *s, int *i)
{
	char	*var_name;

	while (s[*i] && !isquote(s[*i]) && !ft_iswhitespace(s[*i]) \
			&& (ft_isanywordchar(s[*i]) || s[*i] == '?'))
		(*i)++;
	var_name = ft_calloc(*i + 1, sizeof(char));
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, s, *i + 1);
	return (var_name);
}

char	*get_var_value(char *var_name, int *offset, int status)
{
	char	*var_value;

	if (ft_getenv(var_name, 'd') != NULL)
	{
		var_value = ft_strdup(ft_getenv(var_name, 'd'));
		*offset = ft_strlen(var_value) - ft_strlen(var_name);
	}
	else if (!ft_strncmp(var_name, "?", 2))
	{
		var_value = ft_itoa(status);
		*offset = ft_strlen(var_value) - ft_strlen(var_name);
	}
	else
	{
		var_value = ft_strdup("");
		*offset = ft_strlen(var_name) * -1;
	}
	return (var_value);
}

int	deal_with_quotes(char *s, int *quote, int *i)
{
	if (isquote(s[*i]) == 2)
	{
		if (!(*quote))
			*quote = 2;
		else
			*quote = 0;
	}
	if (isquote(s[*i]) == 1 && !(*quote))
	{
		*i += 1;
		while (s[*i] && isquote(s[*i]) != 1)
			*i += 1;
		if (!s[*i])
			return (-1);
	}
	return (0);
}
