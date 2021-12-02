#include "../../includes/minishell.h"

char **g_env;

void	remove_quotes_list(char **command_block)
{
	int i;
	char *temp;

	i = 0;
	while (command_block[i])
	{
		temp =  remove_quotes(command_block[i]);
		command_block[i] = temp;
		i++;
	}
}

int is_empty(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_in_quotes(char *str)
{
	if (str[0] == '\'' || str[ft_strlen(str) - 2] == '\'')
		return (1);
	if (str[0] == '"' || str[ft_strlen(str) - 2] == '"')
		return (2);
	return (0);
}

int check_redirect_type(int redirect_type)
{
	if (redirect_type != 1 && redirect_type != 2 && redirect_type != 3 && redirect_type != 6)
	{
		return (0);
	}
	return (1);
}

void	pick_a_prompt(char **line_from_terminal)
{
	if (isatty(STDIN_FILENO))
	{
		*line_from_terminal = readline("💣-🐚 >  ");
		if (*line_from_terminal)
			add_history(*line_from_terminal);
	}

	else
		get_next_line(STDIN_FILENO, line_from_terminal);
}

int	handle_synthax_error(char *line_from_terminal)
{
	free(line_from_terminal);
	return (2);
}

int	handle_fds_overflow(char **commands, char *line_from_terminal)
{
	if (strlen_list(commands) >= FD_SETSIZE / 2)
	{
		free(line_from_terminal);
		free_str_list(commands, strlen_list(commands));
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

char	***prepare_command_list(char **commands)
{
	int		i;
	char	***command_list;

	i = 0;
	command_list = ft_calloc(sizeof(char ***) , FD_SETSIZE / 2);
	while (commands[i])
	{
		if (!is_empty(commands[i]))
		{
			command_list[i] = ft_better_split(commands[i]);
			command_list[i] = parse_declaration(command_list[i]);
			command_list[i] = parse_block(command_list[i]);
		}
		i++;
	}
	return (command_list);
}

int	parse_command_line(char *line_from_terminal, int *es, int *tmp_es)
{
	char	**commands;
	char	***command_list;
	int		err;

	if (check_syntax(line_from_terminal))
		*es = handle_synthax_error(line_from_terminal);
	else
	{
		line_from_terminal = find_dollars(line_from_terminal, *es);
		commands = ft_pipe_split(line_from_terminal);
		err = handle_fds_overflow(commands, line_from_terminal);
		if (err == 1)
			return (err);
		command_list = prepare_command_list(commands);
		free_str_list(commands, strlen_list(commands));
		*tmp_es = execute(command_list);
		if (*tmp_es >= 0)
			*es = *tmp_es;
		free(command_list);
		free(line_from_terminal);
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	char *line_from_terminal;
	int tmp_es;
	int es;
	(void)argc;
	(void)argv;
	
	init_minishell(env);
	es = 0;
	tmp_es = 0;
	line_from_terminal = NULL;
	while (1)
	{
		pick_a_prompt(&line_from_terminal);
		if (parse_command_line(line_from_terminal, &es, &tmp_es) == 1)
			continue ;
		if (!isatty(STDIN_FILENO))
		{
			if (tmp_es < 0)
				es = tmp_es * -1 - 1;
			break ;
		}
		if (tmp_es < 0)
		{
			es = tmp_es * -1 - 1;
			free_str_list(g_env, strlen_list(g_env));
			break ;
		}
	}
	reset_og_tio_settings();
	return (es);
}
