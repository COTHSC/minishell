#include "../../includes/minishell.h"

int	var_name_match_in_env(char *env_var, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strnstr(env_var, name, len)
		&& (!env_var[len] || env_var[len] == '='))
		return (1);
	else
		return (0);
}

char    *ft_getenv(char *name)
{
    int i;

    i = 0;
    while (g_env[i])
    {
		if (var_name_match_in_env(g_env[i], name))
			return ((ft_strchr(g_env[i], '=')) + 1);
        i++;
    }
    return (NULL);
}
        //if (!ft_strncmp(name, g_env[i], ft_strlen(name)))
