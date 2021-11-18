#include "../../includes/minishell.h"

char **env_selector(int position_selector)
{
	char	**selection;
	int		i;

	selection = calloc_str_list(strlen_list(g_env) + 1);
	i = 0;
	while (g_env[i])
	{
		selection[i] = ft_strdup(g_env[i] + position_selector);
		i++;
	}
	return (selection);
}
