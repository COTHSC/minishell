/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commandline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:57:15 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 21:20:45 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_fds_overflow(char **commands, char *line_from_terminal)
{
	if (strlen_list(commands) >= FD_SETSIZE / 2)
	{
		free(line_from_terminal);
		if (isatty(STDIN_FILENO))
			rl_clear_history();
		free_str_list(commands, strlen_list(commands));
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

static void	free_str_list_ception(char ***trpptrstr)
{
	int	i;

	i = -1;
	while (trpptrstr[++i])
		free_str_list(trpptrstr[i], strlen_list(trpptrstr[i]));
	free(trpptrstr);
}

int	handle_synthax_error(char *line_from_terminal)
{
	free(line_from_terminal);
	return (setcher(2));
}

int	parse_command_line(char *line_from_terminal, int *es)
{
	char	**commands;
	char	***command_list;

	if (basic_checks(line_from_terminal, es))
		return (0);
	else
	{
		line_from_terminal = find_dollars(line_from_terminal, *es);
		commands = ft_pipe_split(line_from_terminal);
		if (handle_fds_overflow(commands, line_from_terminal))
			return (1);
		command_list = prepare_command_list(commands);
		free_str_list(commands, strlen_list(commands));
		if (setcher(-1))
		{
			free(line_from_terminal);
			free_str_list_ception(command_list);
			return (EXIT_FAILURE);
		}
		*es = execute(command_list);
		free(command_list);
		free(line_from_terminal);
	}
	return (EXIT_SUCCESS);
}
