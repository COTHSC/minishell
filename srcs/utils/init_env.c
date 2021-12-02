#include "../../includes/minishell.h"

static int	replace_value(char *tmp, int i)
{
	int	exists;

	exists = 0;
	free(g_env[i]);
	g_env[i] = tmp;
	exists++;
	return (exists);
}

static void	set_env_value(char *var_name, char *var_value)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	int		exists;

	i = -1;
	tmp = ft_strjoin(var_name, "=");
	tmp2 = ft_strjoin(tmp, var_value);
	free(tmp);
	exists = 0;
	while (g_env[++i])
	{
		if (!ft_strncmp(g_env[i], var_name, ft_strlen(var_name)) && \
				(!g_env[i][ft_strlen(var_name)] || \
				g_env[i][ft_strlen(var_name)] == '='))
		{
			exists = replace_value(tmp2, i);
			break ;
		}
	}
	if (!exists)
	{
		g_env = str_add(g_env, tmp2);
		free(tmp2);
	}
}

static char	*increment_shlvl(void)
{
	int	i;

	i = ft_atoi(ft_getenv("SHLVL", 'x'));
	i += 1;
	return (ft_itoa(i));
}

int	init_env(void)
{
	int		i;
	char	*tmp;
	char	*shlvl;

	i = 0;
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
