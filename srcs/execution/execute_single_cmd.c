/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:01:50 by jescully          #+#    #+#             */
/*   Updated: 2021/12/02 17:01:55 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_child_alone(char **cmd)
{
	int		fds[FD_SETSIZE];
	t_redir	redir;
	int		ret;

	init_fds(fds);
	redir.cmd = cmd;
	cmd = ft_redirect(&redir);
	if (redir.es)
		exit(redir.es);
	remove_quotes_list(cmd);
	ret = check_if_file(cmd);
	if (!ret)
		execute_binary(cmd);
	else
		exit(ret);
	return (1);
}

int	execute_builtin_alone(char **cmd)
{
	int		ret;
	int		fds[FD_SETSIZE];
	t_redir	redir;

	redir.cmd = cmd;
	redir.es = 0;
	init_fds(fds);
	redir.es = 0;
	redir.cmd = ft_redirect(&redir);
	remove_quotes_list(redir.cmd);
	ret = 1;
	if (redir.cmd[0] && !redir.es)
		ret = select_builtin_test(builtin_finder(redir.cmd[0]), \
				strlen_list(redir.cmd), redir.cmd);
	close_fds(fds);
	free_str_list(redir.cmd, strlen_list(redir.cmd));
	return (ret);
}

int	fork_and_exec(t_redir redir)
{
	int	status;
	int	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		reset_og_tio_settings();
		execute_child_alone(redir.cmd);
	}
	wait(&status);
	reset_parent_tio_settings();
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	single_cmd(char **cmd)
{
	char	**cmdcmp;
	int		status;
	int		stdio_cpy[2];
	t_redir	redir;

	stdio_cpy[0] = dup(STDIN_FILENO);
	stdio_cpy[1] = dup(STDOUT_FILENO);
	status = 0;
	redir.cmd = cmd;
	cmdcmp = get_command(str_list_dup(redir.cmd));
	if (builtin_finder(cmdcmp[0]) == -1)
	{
		status = fork_and_exec(redir);
	}
	else
	{
		status = execute_builtin_alone(str_list_dup(redir.cmd));
		ft_replug(stdio_cpy);
	}
	free_strs_lists(2, cmdcmp, redir.cmd);
	return (status);
}
