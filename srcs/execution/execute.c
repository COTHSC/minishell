/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:00:06 by jescully          #+#    #+#             */
/*   Updated: 2021/12/07 20:09:50 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_redir	redir;

	status = 0;
	redir.cmd = command_block[0];
	if (command_block[0])
	{
		if (nb_cmds(command_block) > 1)
			return (setcher(ft_multipipes2(command_block)));
		else
			return (setcher(single_cmd(command_block[0])));
	}
	return (status);
}
