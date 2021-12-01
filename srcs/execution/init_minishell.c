#include "../../includes/minishell.h"

int init_minishell(void)
{
	int             check_ret;
	static struct	sigaction sa;

	check_ret = terminal_settings();
	if (check_ret != EXIT_SUCCESS)
	{
		exit(EXIT_FAILURE);
	}
	signal_handler_settings(&sa);
	return (EXIT_SUCCESS);
}
