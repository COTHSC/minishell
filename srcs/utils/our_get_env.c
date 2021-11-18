#include "../../includes/minishell.h"

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
        x_check = ft_strjoin("d", name);
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
