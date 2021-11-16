/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:24:08 by calle             #+#    #+#             */
/*   Updated: 2021/11/16 14:42:37 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_exported_var_with_values( void )
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		if (var_is_exported(g_env[i]) && var_has_value(g_env[i]))
		{
			ft_putstr_fd(&g_env[i][1], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
}

int	ft_env(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		print_usage_env();
		return (2);
	}
	print_exported_var_with_values();
	return (EXIT_SUCCESS);
}
