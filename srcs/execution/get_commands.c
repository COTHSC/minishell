#include "../../includes/minishell.h"

char	**get_filenames_no_redirect(char **command_block, int index, int d)
{
	int		i;
	char	**cmd;

	cmd = command_block;
	i = index;
	while ((command_block[d][i]) && is_redirect(command_block[d][i++]))
		command_block[d][index] = '\0';
	if (command_block[d][i])
		return (cmd);
	else
	{
		get_filenames_no_redirect(command_block, 0, d + 1);
		cmd = delete_str(command_block, d + 1);
	}
	return (cmd);
}

char	**get_command(char **cmd_block)
{
	int	i;
	int	d;
	int	quote;

	i = -1;
	while (cmd_block[++i])
	{
		d = -1;
		while (cmd_block[i][++d])
		{
			if (is_redirect(cmd_block[i][d]))
			{
				cmd_block = get_filenames_no_redirect(cmd_block, d, i);
				if (!cmd_block)
					return (NULL);
				if (ft_strlen(cmd_block[i]) == 0)
					cmd_block = delete_str(cmd_block, i);
				return (get_command(cmd_block));
			}
			quote = isquote(cmd_block[i][d]);
			if (quote)
				d = go_through_quote(cmd_block[i], d, &quote);
		}
	}
	return (cmd_block);
}
