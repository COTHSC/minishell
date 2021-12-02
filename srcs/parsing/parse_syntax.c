#include "../../includes/minishell.h"

int	get_redirect_type(char *s)
{
	int	i;
	int	redirect_type;

	i = 0;
	redirect_type = 0;
	while (s[i] && is_redirect(s[i]))
	{
		redirect_type += is_redirect(s[i]);
		i++;
	}
	return (redirect_type);
}

int	check_quotes(char *s)
{
	int	quote;
	int	i;

	i = 0;
	quote = isquote(s[0]);
	i++;
	while (s[i] && quote)
	{
		if (isquote(s[i]) == quote)
		{
			quote = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_between_the_pipes(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]))
		{
			if (s[i] == '|')
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_between_the_redirects(char *s)
{
	int	i;

	i = 1;
	while (s[i] && is_redirect(s[i]))
		i++;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]))
		{
			if (is_redirect(s[i]))
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (handle_semicolons(s, i))
			return (1);
		if (handle_redirects(s, i))
			return (1);
		if (handle_quotes(s, &i))
			return (1);
		if (handle_pipes(s, i))
			return (1);
		i++;
	}
	return (0);
}
