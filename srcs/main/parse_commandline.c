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

static char	***prepare_command_list(char **commands)
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
			command_list[i] = parse_block(command_list[i]);
			if (setcher(-1))
				return (command_list);
			command_list[i] = parse_declaration(command_list[i]);
		}
		i++;
	}
	return (command_list);
}

static int	handle_synthax_error(char *line_from_terminal)
{
	free(line_from_terminal);
	return (setcher(2));
}

void	free_str_list_ception(char ***trpptrstr)
{
	int i;

	i = -1;
	while (trpptrstr[++i])
		free_str_list(trpptrstr[i], strlen_list(trpptrstr[i]));
	free(trpptrstr);
}

int	parse_command_line(char *line_from_terminal, int *es)
{
	char	**commands;
	char	***command_list;
	int		err;

	err = 0;
	if (!line_from_terminal || !*line_from_terminal)
		return (EXIT_SUCCESS);
	else if (check_syntax(line_from_terminal))
		*es = handle_synthax_error(line_from_terminal);
	else
	{
		line_from_terminal = find_dollars(line_from_terminal, *es);
		commands = ft_pipe_split(line_from_terminal);
		err = handle_fds_overflow(commands, line_from_terminal);
		if (err == 1)
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
