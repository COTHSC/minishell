/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:51:22 by jescully          #+#    #+#             */
/*   Updated: 2021/12/06 18:38:02 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redirect_type(int redirect_type)
{
	return (redirect_type == 1 || redirect_type == 2
		|| redirect_type == 3 || redirect_type == 6);
}

int	handle_semicolons(char *s, int i)
{
	if (s[i] == ';')
	{
		perror_syntax_error(s[i]);
		s[i] = 0;
		return (1);
	}
	return (0);
}

int	handle_redirects(char *s, int i)
{
	if (is_redirect(s[i]))
	{
		if (!check_redirect_type(get_redirect_type(&s[i])))
		{
			perror_syntax_error(s[i]);
			s[i] = 0;
			return (1);
		}
		if (!check_between_the_redirects(&s[i]))
		{
			perror_syntax_error(s[i]);
			s[i] = 0;
			return (1);
		}
	}
	return (0);
}

int	handle_pipes(char *s, int i)
{
	if (s[i] == '|')
	{
		if (!check_between_the_pipes(&s[i]))
		{
			perror_syntax_error(s[i]);
			s[i] = 0;
			return (1);
		}
	}
	return (0);
}

int	handle_quotes(char *s, int *i)
{
	int	quote;

	quote = isquote(s[*i]);
	if (quote)
	{
		if (check_quotes(&s[*i]))
		{
			perror_syntax_error(s[*i]);
			s[*i] = 0;
			return (1);
		}
		*i = go_through_quote(s, *i, &quote);
	}
	return (0);
}
