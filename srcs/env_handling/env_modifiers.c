/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:37:23 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 20:41:03 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_flag(char **var, char flag)
{
	*var[0] = flag;
}

int	alter_env_var(char **clean_env, char *name, char *var_to_add, char *flag)
{
	int		i;
	char	**tmp_env;
	char	*flagged_var_to_add;

	i = index_matching_var_name(clean_env, name);
	flagged_var_to_add = ft_strjoin(flag, var_to_add);
	if (!flagged_var_to_add)
		return (EXIT_FAILURE);
	if (i == -1)
	{
		tmp_env = str_add(g_env, flagged_var_to_add);
		free(flagged_var_to_add);
		if (!tmp_env)
			return (EXIT_FAILURE);
		free_str_list(g_env, strlen_list(g_env));
		g_env = tmp_env;
	}
	else
	{
		free(g_env[i]);
		g_env[i] = flagged_var_to_add;
		if (!g_env[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
