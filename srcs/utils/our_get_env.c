#include "../../includes/minishell.h"

char    *getenv2(char **env, char *name)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(name, env[i], ft_strlen(name)))
            return ((ft_strchr(env[i], '=')) + 1);
        i++;
    }
    return (NULL);
}
