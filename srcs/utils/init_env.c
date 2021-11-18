#include "../../includes/minishell.h"

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
        if (!ft_strncmp(g_env[i], var_name, ft_strlen(var_name)) && (!g_env[i][ft_strlen(var_name)] || g_env[i][ft_strlen(var_name)] == '='))
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
/*
void    set_to_null(char *var)
{
    int i;
    int oldpwd;
    char **newenv;
    char buf[PATH_MAX];

    i = -1;
    oldpwd = 0;
    if (!ft_getenv("OLDPWD=", 'x'))
    {
        newenv = str_add(g_env, "xOLDPWD");
        free_str_list(g_env, strlen_list(g_env));
        g_env = newenv;
        return;
    }
    while (g_env[++i])
    {
        if (!ft_strncmp(var, g_env[i], ft_strlen(var)) && (!g_env[i][ft_strlen(var)] || g_env[i][ft_strlen(var)] == '='))
        {
           // free(g_env[i]);
            set_env_value("xOLDPWD", getcwd(buf, PATH_MAX));
           // tmp = ft_strdup("xOLDPWD");
           // g_env[i] = tmp;
            oldpwd++;
        }
    }

}

*/

char *increment_shlvl()
{
    int i;

    i = ft_atoi(ft_getenv("SHLVL", 'x'));
    i += 1;
    return (ft_itoa(i));
}

int init_env(void)
{
    int i;
    int oldpwd;
    char *tmp;
    char *shlvl;

    i = 0;
    oldpwd = 0;
    if (!match_var_name(g_env, "OLDPWD"))
        alter_env_var(g_env, "OLDPWD", "", "x");
    while (g_env[i])
    {
        tmp = ft_strjoin("x", g_env[i]);
        free(g_env[i]);
        g_env[i] = tmp;
        i++;
    }

    shlvl = increment_shlvl();
    set_env_value("xSHLVL", shlvl);
    free(shlvl);
    return (0);
}


