/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_selector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:39:57 by calle             #+#    #+#             */
/*   Updated: 2021/12/02 14:39:58 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

enum e_builtins {e_cd, e_pwd};

int	select_builtin_test(int index, int argc, char **argv)
{
	static int	(*builtin_lookup[7])(int argc, char **args) = {
		ft_cd, ft_pwd, ft_exit, ft_export, ft_env, ft_unset, ft_echo};

	return (builtin_lookup[index](argc, argv));
}
