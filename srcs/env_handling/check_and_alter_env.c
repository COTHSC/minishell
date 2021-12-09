/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_alter_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:42:15 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 20:42:35 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_env_wrapper(char *arg, char *flag, char **clean_env)
{
	int		iie;
	char	**name_value_pair;
	int		ret_value;

	ret_value = 0;
	name_value_pair = split_to_name_value_pair(arg);
	iie = index_matching_var_name(clean_env, name_value_pair[0]);
	if (ft_strlen(name_value_pair[0]) == 1 && arg[0] == '_')
		;
	else if (ft_strncmp(flag, "x", 1) == 0 && !has_valid_var_name(arg))
	{
		perror_not_a_valid_identifier(arg, "export");
		ret_value = 1;
	}
	else if (iie == -1 || (flag[0] == 'd' && !var_is_exported(g_env[iie])))
		ret_value = alter_env_var(clean_env, name_value_pair[0], arg, flag);
	else if (flag[0] == 'x' && !var_has_value(arg))
		change_flag(&g_env[iie], flag[0]);
	else
		ret_value = alter_env_var(clean_env, name_value_pair[0], arg, "x");
	free_str_list(name_value_pair, strlen_list(name_value_pair));
	return (ret_value);
}

int	check_and_alter_env(char **args, char *flag)
{
	int		i;
	char	**clean_env;
	int		ret_value;

	clean_env = env_selector(1, NULL);
	ret_value = 0;
	i = 0;
	while (args[i])
	{
		if (check_env_wrapper(args[i], flag, clean_env) != 0)
			ret_value = 1;
		i++;
	}
	free_str_list(clean_env, strlen_list(clean_env));
	return (ret_value);
}
