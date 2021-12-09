/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:42:59 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 20:48:04 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_through_quote(char const *s, int lead, int *quote)
{
	while (*quote)
	{
		lead++;
		if (isquote(s[lead]) == *quote)
			*quote = 0;
	}
	return (lead);
}

int	isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	else
		return (0);
}

int	var_name_match_in_env(char *env_var, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(env_var, name, len) && (!env_var[len] \
				|| env_var[len] == '='))
		return (1);
	else
		return (0);
}

static char	*wrapper_get_env(char *x_check, char *env_var, char c)
{
	free(x_check);
	return ((ft_strchr(env_var, c)) + 1);
}

char	*ft_getenv(char *name, char c)
{
	int		i;
	char	*x_check;

	if (c == 'x')
		x_check = ft_strjoin("x", name);
	else
		x_check = ft_strdup(name);
	i = -1;
	while (g_env[++i])
	{
		if (c == 'x')
		{
			if (var_name_match_in_env(g_env[i], x_check))
				return (wrapper_get_env(x_check, g_env[i], '='));
		}
		else if (var_name_match_in_env(&g_env[i][1], name))
			return (wrapper_get_env(x_check, g_env[i], '='));
	}
	free(x_check);
	return (NULL);
}
