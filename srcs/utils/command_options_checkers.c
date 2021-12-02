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

int	option_is_called_and_repeated(char *cmd_block, char *option)
{
	int		i;
	char	option_letter;

	if (!cmd_block || ft_strncmp(cmd_block, option, ft_strlen(option)) != 0)
		return (0);
	i = 2;
	option_letter = option[1];
	while (cmd_block[i])
	{
		if (cmd_block[i] != option_letter)
			return (0);
		i++;
	}
	return (1);
}
