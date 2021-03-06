/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:15:31 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 22:36:35 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_status(char *arg)
{
	int		i;
	char	sign;	

	i = 0;
	sign = 0;
	if (*arg == 0)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
		{
			if (sign != 0)
				return (0);
			else
				sign = arg[i];
		}
		else if (!ft_isdigit(arg[i]) && !ft_iswhitespace(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_exit_with_a_status(char *status)
{
	int				out_of_range;
	unsigned char	exit_status;

	out_of_range = 0;
	exit_status = (unsigned char)ft_strtoll(status, &out_of_range);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit \n", STDERR_FILENO);
	if (out_of_range == 1)
	{
		perror_numeric_arg_required(status, "exit");
		exit (2);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(exit_status);
}

static void	actually_exit(int argc, char **argv)
{
	free_str_list(g_env, strlen_list(g_env));
	reset_og_tio_settings();
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit \n", STDERR_FILENO);
		exit(0);
	}
	else if (!is_valid_status(argv[1]))
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit \n", STDERR_FILENO);
		perror_numeric_arg_required(argv[1], "exit");
		exit(2);
	}
	else
		handle_exit_with_a_status(argv[1]);
	exit(0);
}

int	ft_exit(int argc, char **argv)
{
	if (argc > 2 && is_valid_status(argv[1]))
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit \n", STDERR_FILENO);
		perror_too_many_args("exit");
		return (1);
	}
	else
		actually_exit(argc, argv);
	return (0);
}
