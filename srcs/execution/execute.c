#include "../../includes/minishell.h"

int	execute_child_piped(int (*fd)[2], int i, int n, char **cmd)
{
	int		fds[FD_SETSIZE];
	t_redir	redir;
	int		ret;

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
	return (0);
}

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
		ret = select_builtin_test(builtin_finder(redir.cmd[0]), strlen_list(redir.cmd), redir.cmd);
	close_fds(fds);
	free_str_list(redir.cmd, strlen_list(redir.cmd));
	return (ret);
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
	redir.es = 0;
	redir.cmd = ft_redirect(&redir);
	remove_quotes_list(redir.cmd);
	ret = 1;
	if (redir.cmd[0] && !redir.es)
		ret = select_builtin_test(builtin_finder(redir.cmd[0]), strlen_list(redir.cmd), redir.cmd);
	close_fds(fds);
	close(fd[i][0]);
	close(fd[i + 1][1]);
	free_str_list(redir.cmd, strlen_list(redir.cmd));
	exit (ret);
}

int	count_and_check(char ***cmd, int fd[FD_SETSIZE / 2][2])
{
	int n;

	n = nb_cmds(cmd);
	if (n >= FD_SETSIZE / 2)
		return (-1);
	if (make_pipes(fd, n))
		return (-1);
	return (n);
}

int fork_and_exec(t_redir redir)
{
	int status;
	int pid;

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

int fork_and_sort(char **cmd, int i, int n, int fd[FD_SETSIZE / 2][2])
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
		reset_og_tio_settings();
		if (builtin_finder(cmdcmp[0]) == -1)
			execute_child_piped(fd, i, n, cmd);
		else
			status = execute_builtin_piped(fd, i, n, cmd);
	}
	free_list_and_return_null(cmdcmp, strlen_list(cmdcmp));
	free_list_and_return_null(cmd, strlen_list(cmd));
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
	while (++i < n)
		status = fork_and_sort(cmd[i], i, n, fd);
	close_unused_fds(fd, n + 1, n);
	status = wait_and_get_status();
	reset_parent_tio_settings();
	close(fd[n][1]);
	close(fd[n][0]);
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
	free_list_and_return_null(cmdcmp, strlen_list(cmdcmp));
	free_list_and_return_null(redir.cmd, strlen_list(redir.cmd));
	return (status);
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
