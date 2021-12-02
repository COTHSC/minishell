#include "../../includes/minishell.h"

char	*get_var_name(char *s, int *i)
{
	char	*var_name;

	while (s[*i] && !isquote(s[*i]) && !ft_iswhitespace(s[*i]) && ft_isanywordchar(s[*i]))//s[*i] != '$' && s[*i] != '=')
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
		var_value = NULL;
		*offset = ft_strlen(var_name) * -1;
	}
	return (var_value);
}

char	*exp_rep(char *s, char *var_value, char *var_name, int offset, int i)
{
	unsigned long int	d;
	char				*newstr;

	d = 0;
	if (offset < 0)
	{
		newstr = ft_strdup(&s[-offset]);
		while (d < ft_strlen(var_name) + offset)
		{
			newstr[d] = var_value[d];
			d++;
		}
	}
	else
	{
		newstr = ft_calloc(ft_strlen(s) + offset + 1, sizeof(char));
		while (d <= offset + ft_strlen(var_name))
		{
			newstr[d] = var_value[d];
			d++;
		}
		ft_strlcpy(&newstr[ft_strlen(var_value)], &s[i], ft_strlen(s) - i + 1);
	}
	return (newstr);
}

int	is_done(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!isquote(s[i]) && s[i] != '/' && s[i] != '%')
			return (0);
		i++;
	}
	return (1);
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
	newstr = exp_rep(s, var_value, var_name, offset, i);
	if (var_value)
		free(var_value);
	free(var_name);
	if (newstr[0] == '$')
		*index = *index - 1;
	return (newstr);
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

char	*find_dollars(char *s, int status)
{
	int		i;
	char	*newend;
	char	*news;
	int		d;
	int		quote;

	i = -1;
	quote = 0;
	while (s && s[++i])
	{
		if (deal_with_quotes(s, &quote, &i) == -1)
			return (s);
		if (s[i] == '$')
		{
			newend = expand_vars(&s[i + 1], status, quote, &i);
			s[i] = 0;
			news = ft_strjoin(s, newend);
			free(newend);
			d = ft_strlen(s);
			free(s);
			s = news;
			if (!s[i])
				return (s);
		}
	}
	return (s);
}
