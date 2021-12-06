#include "../../includes/minishell.h"

void	remove_quotes_list(char **command_block)
{
	int		i;
	char	*temp;

	i = 0;
	while (command_block[i])
	{
		temp = remove_quotes(command_block[i]);
		command_block[i] = temp;
		i++;
	}
}
