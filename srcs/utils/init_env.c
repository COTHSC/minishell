#include "../../includes/minishell.h"

void    set_to_null(char *var)
{
    int i;
    char *tmp;
    int oldpwd;
    char **newenv;

    i = -1;
    oldpwd = 0;
    while (g_env[++i])
    {
        if (ft_strnstr(var, g_env[i], ft_strlen(var)) && (!g_env[i][ft_strlen(var)] || g_env[i][ft_strlen(var)] == '='))
        {
            free(g_env[i]);
            tmp = ft_strdup("OLDPWD");
            g_env[i] = tmp;
            oldpwd++;
        }
    }
    if (!oldpwd)
    {
        newenv = str_add(g_env, "OLDPWD");
        free_str_list(g_env, strlen_list(g_env));
        g_env = newenv;
    }
}

void    set_env_value(char *var_name, char *var_value)
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
    while (g_env[++i])
    {
        if (ft_strnstr(g_env[i], var_name, ft_strlen(var_name)) && (!g_env[i][ft_strlen(var_name)] || g_env[i][ft_strlen(var_name)] == '='))
        {
            free(g_env[i]);
            g_env[i] = tmp2;
            exists++;
            if (exists)
                break;
        }
    }
    if (!exists)
    {
        g_env = str_add(g_env, tmp2);
        free(tmp2);
    }

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
    char *shlvl;

    i = 0;
    oldpwd = 0;
    set_to_null("OLDPWD");
    set_env_value("PWD", getcwd(buf, PATH_MAX));
    shlvl = increment_shlvl();
    set_env_value("SHLVL", shlvl);
    free(shlvl);
    while (g_env[i])
 {
   tmp = ft_strjoin("x", g_env[i]);
        free(g_env[i]);
        g_env[i] = tmp;
        i++;
    }
    return (0);
}


