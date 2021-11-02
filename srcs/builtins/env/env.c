/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:24:08 by calle             #+#    #+#             */
/*   Updated: 2021/10/28 19:12:32 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	print_exported_var_with_values(char **var_list)
{
	int	i;

	i = 0;
	while (var_list[i])
	{
		if (var_is_exported(var_list[i] && extract
		{
			ft_putstr_fd(str_list[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
}

int	ft_env(int argc, char **argv, char ***env)
{
	(void)argc;
//	(void)argv;
//	if (argc != 1)
//	{
//		errno = 1;
//		perror(NULL);
//		return (EXIT_FAILURE);
//	}
	print_exported_var_with_value(*env);
	print_str_if_value_is_defined(argv + 1);
	return (EXIT_SUCCESS);
}
