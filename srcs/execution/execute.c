#include "../../includes/minishell.h"

int	nb_cmds(char ***cmd)
{
	int	n;

	n = 0;
	while (cmd[n])
		n++;
	return (n);
}

int	execute(char ***command_block)
{
	int		status;
	int		stdio_cpy[2];
	t_redir	redir;

	stdio_cpy[0] = dup(STDIN_FILENO);
	stdio_cpy[1] = dup(STDOUT_FILENO);
	status = 0;
	redir.cmd = command_block[0];
	if (command_block[0])
	{
		if (nb_cmds(command_block) > 1)
			return (ft_multipipes2(command_block));
		else
			return (single_cmd(command_block[0]));
	}
	return (status);
}
