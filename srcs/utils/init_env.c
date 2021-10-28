#include "../../includes/minishell.h"

void    set_to_null(char ***env2, char *var)
{
    int i;
    char *tmp;
    char **env;
    int oldpwd;

    i = -1;
    env = *env2;
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

void    set_init_value(char ***env2, char *var, char *var_value)
{
    int i;
    char *tmp;
    char *tmp2;
    char **env;
    int oldpwd;

    i = -1;
    env = *env2;
    oldpwd = 0;
    tmp = ft_strjoin(var, "=");
    tmp2 = ft_strjoin(tmp, var_value);
    free(tmp);
    while (env[++i])
    {
        if (ft_strnstr(env[i], var, ft_strlen(var)) && (!env[i][ft_strlen(var)] || env[i][ft_strlen(var)] == '='))
        {
            env[i] = tmp2;
         //   free(tmp2);
            oldpwd++;
        }
    }
    if (!oldpwd)
        str_add(env, tmp2);
}

char *increment_shlvl(char **env)
{
    int i;

    i = ft_atoi(getenv2(env, "SHLVL"));
    i += 1;
    return (ft_itoa(i));
}

int init_env(char ***env2)
{
    int i;
    int oldpwd;
    char *tmp;
    char **env;
    char buf[PATH_MAX];

    env = *env2;
    i = 0;
    oldpwd = 0;
    set_to_null(env2, "OLDPWD");
    set_init_value(env2, "PWD", getcwd(buf, PATH_MAX));
    set_init_value(env2, "SHLVL", increment_shlvl(env));
    while (env[i])
    {
        tmp = ft_strjoin("x",env[i]);
        free(env[i]);
        env[i] = tmp;
        i++;
    }
    *env2 = env;
    print_str_list(*env2, "");
    return (0);
}


