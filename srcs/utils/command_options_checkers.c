#include "../../includes/minishell.h"

int	is_option(char *cmd_block)
{
	return (*cmd_block == '-');
}

int	option_is_called(char *cmd_block, char *option)
{
	if (ft_strncmp(cmd_block, option, max_strlen(cmd_block, option)) == 0)
		return (1);
	else
		return (0);
}
