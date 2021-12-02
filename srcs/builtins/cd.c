/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:42:58 by calle             #+#    #+#             */
/*   Updated: 2021/12/02 14:43:00 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_args_errors(int nb_arg, char *option)
{
	if (nb_arg > 1 && is_option(option))
	{
		perror_invalid_option("cd", option, "");
		print_usage_cd();
		return (2);
	}
	if (nb_arg > 2)
	{
		perror_too_many_args("cd");
		return (1);
	}
	return (0);
}

int	move_to_another_dir(DIR *dir_pointer, const char *req_path)
{
	if (!dir_pointer)
	{
		print_minishell_error(errno, "cd", (char *)req_path);
		return (EXIT_FAILURE);
	}
	else
	{
		closedir(dir_pointer);
		if (chdir(req_path) == -1)
		{
			print_minishell_error(errno, "cd", (char *)req_path);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
}

int	ft_cd(int argc, char **argv)
{
	const char	*req_path;
	DIR			*dir_pointer;
	int			test_err;

	req_path = argv[1];
	if (argc == 1)
	{
		req_path = ft_getenv("HOME", 'd');
		if (!req_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (EXIT_FAILURE);
		}
	}
	test_err = handle_args_errors(argc, argv[1]);
	if (test_err > 0)
		return (test_err);
	dir_pointer = opendir(req_path);
	return (move_to_another_dir(dir_pointer, req_path));
}
