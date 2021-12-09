/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_builtins_usage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 21:00:21 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 21:00:24 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_usage_export(void)
{
	ft_putstr_fd("export: usage: ", 2);
	ft_putstr_fd("export [name[=value] ...]", 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage_unset(void)
{
	ft_putstr_fd("unset: usage: ", 2);
	ft_putstr_fd("unset [name ...]", 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage_env(void)
{
	ft_putstr_fd("env: usage: ", 2);
	ft_putstr_fd("env", 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage_cd(void)
{
	ft_putstr_fd("cd: usage: ", 2);
	ft_putstr_fd("cd [dir]", 2);
	ft_putchar_fd('\n', 2);
}
