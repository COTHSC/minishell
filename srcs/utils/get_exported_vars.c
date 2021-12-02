#include "../../includes/minishell.h" 

int	count_exported_vars(char **env)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (env[++i])
	{
		if (env[i][0] == 'x')
			c++;
	}
	return (c);
}

char	**ft_exported_vars(char select)
{
	int		i;
	int		c;
	char	**clean_g_env;

	i = -1;
	c = 0;
	clean_g_env = (char **)calloc_str_list(count_exported_vars(g_env) + 1);
	while (g_env[++i])
	{
		if (g_env[i][0] == select)
		{
			clean_g_env[c] = &g_env[i][1];
			c++;
		}
	}
	clean_g_env[(count_exported_vars(g_env) - 1)] = NULL;
	return (clean_g_env);
}
