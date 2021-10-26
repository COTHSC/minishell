/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:24:08 by calle             #+#    #+#             */
/*   Updated: 2021/10/26 16:03:56 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

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
	print_str_list(*env, NULL);
	print_str_list(argv + 1, NULL);
	return (EXIT_SUCCESS);
}
