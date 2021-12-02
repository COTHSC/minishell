#include "../../includes/minishell.h"

int	count_env_vars_with_flag(char **env, char flag)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (env[i])
	{
		if (env[i][0] == flag)
			counter++;
		i++;
	}
	return (counter);
}

char	**env_selector(int position_selector, char *flag)
{
	char	**selection;
	int		i;
	int		counter;

	if (flag && (flag[0] == 'x' || flag[0] == 'd'))
		counter = count_env_vars_with_flag(g_env, flag[0]);
	else
		counter = strlen_list(g_env);
	selection = calloc_str_list(counter + 1);
	i = 0;
	counter = 0;
	while (g_env[i])
	{
		if (flag && (g_env[i][0] == flag[0]))
		{
			selection[counter] = ft_strdup(g_env[i] + position_selector);
			counter++;
		}
		if (!flag)
			selection[i] = ft_strdup(g_env[i] + position_selector);
		i++;
	}
	return (selection);
}
