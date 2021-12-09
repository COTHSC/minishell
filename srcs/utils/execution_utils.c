/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:02:50 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 23:06:25 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_and_get_status(void)
{
	int		status;
	int		i;
	pid_t	wpid;

	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(&status);
		i = 1;
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WTERMSIG(status) == 13)
		status = 0;
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}

void	free_command_block(char **command_block)
{
	int	d;

	d = 0;
	while (command_block[d])
		free(command_block[d++]);
	free(command_block);
}

void	ft_replug(int stdio_cpy[2])
{
	dup2(stdio_cpy[0], STDIN_FILENO);
	dup2(stdio_cpy[1], STDOUT_FILENO);
}

int	execute_binary(char **command_block)
{
	char	*path;
	char	**clean_env;

	path = get_path(command_block);
	clean_env = ft_exported_vars('x');
	if ((execve(path, command_block, clean_env)) == -1)
	{
		free(path);
		exit(EXIT_FAILURE);
	}
	exit (0);
}

int	check_if_file(char **cmd)
{
	if (is_path(cmd[0]))
	{
		if (access(cmd[0], F_OK) != 0)
		{
			print_minishell_error(errno, NULL, cmd[0]);
			return (127);
		}
		else if (access(cmd[0], X_OK) != 0)
		{
			print_minishell_error(errno, NULL, cmd[0]);
			return (126);
		}
	}
	return (0);
}
