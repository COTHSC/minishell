#include "../../includes/minishell.h"

char    *getenv2(char *name)
{
    int i;

    i = 0;
    while (g_env[i])
    {
        if (!ft_strncmp(name, g_env[i], ft_strlen(name)))
            return ((ft_strchr(g_env[i], '=')) + 1);
        i++;
    }
    return (NULL);
}
