#include "../../includes/minishell.h"

static char	**create_basic(void)
{
	char	**env4;
	char	buf[PATH_MAX];
	char	*cwd;

	cwd = ft_strdup(getcwd(buf, PATH_MAX));
	if (!cwd)
		return (NULL);
	env4 = calloc_str_list(4);
	env4[0] = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!env4[0])
	{
		free(env4);
		return (NULL);
	}
	env4[1] = ft_strdup("OLDPWD");
	if (!env4[1])
		return (free_list_and_return_null(env4, 1));
	env4[2] = ft_strdup("SHLVL=");
	if (!env4[2])
		return (free_list_and_return_null(env4, 2));
	return (env4);
}

int	init_minishell(char **env)
{
	int						check_ret;

	check_ret = terminal_settings();
	if (check_ret != EXIT_SUCCESS)
	{
		exit(EXIT_FAILURE);
	}
	signal_handler_settings();
	if (!env[0])
		g_env = create_basic();
	else
		g_env = str_list_dup(env);
	if (!g_env)
		exit(EXIT_FAILURE);
	init_env();
	return (EXIT_SUCCESS);
}
