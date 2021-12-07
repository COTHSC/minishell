#include "../../includes/minishell.h"

char	**g_env;

static void	pick_a_prompt(char **line_from_terminal)
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

static int	reset_og_term_and_return(int es)
{
	reset_og_tio_settings();
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	return (es);
}

static void	set_exit_status(int tmp_es, int *es)
{
	if (tmp_es < 0)
		*es = tmp_es * -1 - 1;
}

int	main(int argc, char **argv, char **env)
{
	char	*line_from_terminal;
	int		tmp_es;
	int		es;

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
		set_exit_status(tmp_es, &es);
		if (!isatty(STDIN_FILENO))
		{
			free_str_list(g_env, strlen_list(g_env));
			break ;
		}
		if (tmp_es < 0)
			break ;
	}
	return (reset_og_term_and_return(es));
}
