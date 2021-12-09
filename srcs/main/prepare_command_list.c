/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:54:42 by calle             #+#    #+#             */
/*   Updated: 2021/12/09 23:19:26 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	basic_checks(char *line_from_terminal, int *es)
{
	if (!line_from_terminal || !*line_from_terminal)
	{
		free(line_from_terminal);
		return (1);
	}
	else if (check_syntax(line_from_terminal))
	{
		*es = handle_synthax_error(line_from_terminal);
		return (1);
	}
	return (0);
}

char	***prepare_command_list(char **commands)
{
	int		i;
	char	***command_list;

	i = 0;
	setcher(0);
	command_list = ft_calloc(sizeof(char ***), FD_SETSIZE / 2);
	while (commands[i])
	{
		if (!is_empty(commands[i]))
		{
			command_list[i] = ft_better_split(commands[i]);
			command_list[i] = parse_declaration(command_list[i]);
			command_list[i] = parse_block(command_list[i]);
			if (setcher(-1))
				return (command_list);
		}
		i++;
	}
	return (command_list);
}
