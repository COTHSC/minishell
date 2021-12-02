#include "../../includes/minishell.h"

static char	**create_basic()
{
	char **env4;
	char buf[PATH_MAX];
	char *cwd;

	cwd = ft_strdup(getcwd(buf, PATH_MAX));
	if (!cwd)
		return (NULL);
	env4 = calloc_str_list(4);
	env4[0] = ft_strjoin("PWD=", cwd);
	env4[1] = ft_strdup("OLDPWD");
	env4[2] = ft_strdup("SHLVL=");
	free(cwd);
	if (!env4[0])
		return (NULL);
	if (!env4[1])
	{
		free(env4[0]);
		return (NULL);
	}
	if (!env4[2])
	{
		free(env4[0]);
		free(env4[1]);
		return (NULL);
	}
	return (env4);
}

int	init_minishell(char **env)
{
	int						check_ret;
	static struct			sigaction	sa;

	check_ret = terminal_settings();
	if (check_ret != EXIT_SUCCESS)
	{
		exit(EXIT_FAILURE);
	}
	signal_handler_settings(&sa);
	if (!env[0])
		g_env = create_basic();
	else
		g_env = str_list_dup(env);
	if (!g_env)
		exit(EXIT_FAILURE);
	init_env();
	return (EXIT_SUCCESS);
}
