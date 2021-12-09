/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:00:22 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 18:00:30 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_and_check(char ***cmd, int fd[FD_SETSIZE / 2][2])
{
	int	n;

	n = nb_cmds(cmd);
	if (n >= FD_SETSIZE / 2)
		return (-1);
	if (make_pipes(fd, n))
		return (-1);
	return (n);
}

void	execute_child_piped(int (*fd)[2], int i, int n, char **cmd)
{
	int		fds[FD_SETSIZE];
	t_redir	redir;
	int		ret;

	redir.es = 0;
	init_fds(fds);
	redir.cmd = cmd;
	close_unused_fds(fd, i, n);
	dup2(fd[i][0], STDIN_FILENO);
	if (i != n - 1)
		dup2(fd[i + 1][1], STDOUT_FILENO);
	cmd = ft_redirect(&redir);
	if (redir.es)
		exit(redir.es);
	remove_quotes_list(cmd);
	ret = check_if_file(cmd);
	if (!ret)
		execute_binary(cmd);
	else
	{
		close_fds(fds);
		close(fd[i][0]);
		close(fd[i + 1][1]);
		exit(ret);
	}
}

int	execute_builtin_piped(int (*fd)[2], int i, int n, char **cmd)
{
	int		ret;
	int		fds[FD_SETSIZE];
	t_redir	redir;

	redir.cmd = cmd;
	redir.es = 0;
	init_fds(fds);
	close_unused_fds(fd, i, n);
	dup2(fd[i][0], STDIN_FILENO);
	if (i != n - 1)
		dup2(fd[i + 1][1], STDOUT_FILENO);
	redir.cmd = ft_redirect(&redir);
	remove_quotes_list(redir.cmd);
	ret = 1;
	if (redir.cmd[0] && !redir.es)
		ret = select_builtin_test(builtin_finder(redir.cmd[0]), \
				strlen_list(redir.cmd), redir.cmd);
	close_fds(fds);
	close(fd[i][0]);
	close(fd[i + 1][1]);
	free_str_list(redir.cmd, strlen_list(redir.cmd));
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit (ret);
}

int	fork_and_sort(char **cmd, int i, int n, int fd[FD_SETSIZE / 2][2])
{
	char	**cmdcmp;
	int		pids[FD_SETSIZE / 2];
	int		status;

	status = 0;
	cmdcmp = str_list_dup(cmd);
	cmdcmp = get_command(cmdcmp);
	pids[i] = fork();
	if (pids[i] == 0)
	{
		if (builtin_finder(cmdcmp[0]) == -1)
			execute_child_piped(fd, i, n, cmd);
		else
			status = execute_builtin_piped(fd, i, n, cmd);
	}
	free_strs_lists(2, cmdcmp, cmd);
	return (status);
}

int	ft_multipipes2(char ***cmd)
{
	int		fd[FD_SETSIZE / 2][2];
	int		i;
	int		n;
	int		status;

	n = count_and_check(cmd, fd);
	if (n == -1)
		return (1);
	i = -1;
	reset_og_tio_settings();
	while (++i < n)
	{
		status = fork_and_sort(cmd[i], i, n, fd);
	}
	close_unused_fds(fd, n + 1, n);
	status = wait_and_get_status();
	reset_parent_tio_settings();
	close(fd[n][1]);
	close(fd[n][0]);
	return (status);
}
