/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:24:08 by calle             #+#    #+#             */
/*   Updated: 2021/11/15 18:54:24 by calle            ###   ########.fr       */
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
	(void)argc;
	(void)argv;
//	if (argc != 1)
//	{
//		errno = 1;
//		perror(NULL);
//		return (EXIT_FAILURE);
//	}
	print_exported_var_with_values();
	print_str_list(argv + 1, NULL);
	return (EXIT_SUCCESS);
}
