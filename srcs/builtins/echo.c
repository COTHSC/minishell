/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:51:41 by calle             #+#    #+#             */
/*   Updated: 2021/12/02 11:16:12 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	print_multiple_arguments(char **args, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i != end - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	is_only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static int	valid_n_option(char *option)
{
	if (ft_strnstr(option, "-n", max_strlen(option, "-n")) - option == 0)
	{
		if (is_only_char((option + 1), 'n'))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static int	count_valid_successive_options(char **args)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (args[i])
	{
		if (!valid_n_option(args[i]))
			break ;
		counter++;
		i++;
	}
	return (counter);
}

int	ft_echo(int argc, char **argv)
{
	int	num_options;

	num_options = count_valid_successive_options(argv) + 1;
	if (argc == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else if (num_options > 1)
	{
		print_multiple_arguments(argv, num_options, strlen_list(argv));
		return (EXIT_SUCCESS);
	}
	else
	{
		print_multiple_arguments(argv, 1, strlen_list(argv));
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
}
