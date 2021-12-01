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

void	init_to_zero(int num, ...)
{
	va_list	arguments;
	int		x;

	x = 0;
	va_start(arguments, num);
	while (x++ < num)
		*(va_arg(arguments, int *)) = 0;
	va_end(arguments);
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
	if (!ft_strncmp(env_var, name, len) && (!env_var[len] || env_var[len] == '='))
		return (1);
	else
		return (0);
}

char    *ft_getenv(char *name, char c)
{
    int i;
    char *x_check;
    
    if (c == 'x')
        x_check = ft_strjoin("x", name);
    else
        x_check = ft_strdup(name);
    i = 0;
    while (g_env[i])
    {
        if (c == 'x')
        {
            if (var_name_match_in_env(g_env[i], x_check))
            {
                free(x_check);
                return ((ft_strchr(g_env[i], '=')) + 1);
            }
        }
        else if (var_name_match_in_env(&g_env[i][1], name))
        {
            free(x_check);
            return ((ft_strchr(g_env[i], '=')) + 1);
        }
        i++;
    }
    free(x_check);
    return (NULL);
}
