#include "../../includes/minishell.h"

int init_env(char **env2)
{
    int i;
    char *tmp;

    i = -1;
    while (env2[++i])
    {
        tmp = ft_strjoin("x", env2[i]);
        free(env2[i]);
        env2[i] = tmp;
    }
    
    return (0);
}

void    set_oldpwd(char **env2)
{
    int i;
    int tmp;

    i = -1;
    while (env2[++i])
    {
        tmp = ft_strjoin("x", env2[i]);
        free(env2[i]);
        env2[i] = tmp;
    }
}
