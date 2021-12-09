#include "../../includes/minishell.h"

char	**g_env;

int setcher(int newvalue)
{
	static int ret = 0;

	if (newvalue >= 0)
		ret = newvalue;
	return (ret);
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
	{
		get_next_line(STDIN_FILENO, line_from_terminal);
		if (!line_from_terminal)
			exit(0);
	}
}

static int	reset_og_term_and_return(int es)
{
	reset_og_tio_settings();
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	return (es);
}

int	main(int argc, char **argv, char **env)
{
	char	*line_from_terminal;
	int		es;

	(void)argc;
	(void)argv;
	init_minishell(env);
	es = 0;
	line_from_terminal = NULL;
	while (1)
	{
		pick_a_prompt(&line_from_terminal);
		if (parse_command_line(line_from_terminal, &es) == 1)
			continue ;
		es = setcher(-1);
		if (!isatty(STDIN_FILENO))
		{
			free_str_list(g_env, strlen_list(g_env));
			break ;
		}
	}
	return (reset_og_term_and_return(es));
}
