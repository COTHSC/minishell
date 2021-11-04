#include "../../includes/minishell.h"

void    set_to_null(char **env2, char *var)
{
    int i;
    char *tmp;
    char **env;
    int oldpwd;

    i = -1;
    env = env2;
    oldpwd = 0;
    while (env[++i])
    {
        if (ft_strnstr(env[i], var, ft_strlen(var)) && (!env[i][ft_strlen(var)] || env[i][ft_strlen(var)] == '='))
        {
            tmp = ft_strdup("OLDPWD");
            env[i] = tmp;
            oldpwd++;
        }
    }
    if (!oldpwd)
        str_add(env, "OLDPWD");
}

void    set_env_value(char **env, char *var_name, char *var_value)
{
    int i;
    char *tmp;
    char *tmp2;
    int exists;

    i = -1;
    exists = 0;
    tmp = ft_strjoin(var_name, "=");
    tmp2 = ft_strjoin(tmp, var_value);
    free(tmp);
    while (env[++i])
    {
        if (ft_strnstr(env[i], var_name, ft_strlen(var_name)) && (!env[i][ft_strlen(var_name)] || env[i][ft_strlen(var_name)] == '='))
        {
            free(env[i]);
            env[i] = tmp2;
            exists++;
        }
    }
    if (!exists)
        str_add(env, tmp2);
}

char *increment_shlvl()
{
    int i;

    i = ft_atoi(ft_getenv("SHLVL"));
    i += 1;
    return (ft_itoa(i));
}

int init_env(void)
{
    int i;
    int oldpwd;
    char *tmp;
    char buf[PATH_MAX];

    i = 0;
    oldpwd = 0;
    set_to_null(g_env, "OLDPWD");
    set_env_value(g_env, "PWD", getcwd(buf, PATH_MAX));
    set_env_value(g_env, "SHLVL", increment_shlvl());
    while (g_env[i])
    {
        tmp = ft_strjoin("x", g_env[i]);
        free(g_env[i]);
        g_env[i] = tmp;
        i++;
    }
    print_str_list(g_env, "");
    return (0);
}


