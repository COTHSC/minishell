#include "../../includes/minishell.h"

int	check_fd(int fd, char *filename)
{
	char	*pwd;
	char	*temp;
	char	*temp1;

	pwd = NULL;
	if (!is_path(filename))
	{
		temp = getenv("PWD");
		temp1 = ft_strjoin(temp, "/");
		pwd = ft_strjoin(temp1, filename);
		free(temp1);
	}
	if (fd < 0)
	{
		if (access(pwd, F_OK) == 0)
			print_file_error(errno, filename);
		else
			print_file_error(errno, filename);
		if (pwd)
			free(pwd);
		return (1);
	}
	if (pwd)
		free(pwd);
	return (0);
}

int	open_file(int *fd, int redirect_type, char *file_name)
{
	int	invalid_fd;

	if (redirect_type == 2)
		*fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (redirect_type == 3)
		*fd = open(file_name, O_RDONLY, 0777);
	else if (redirect_type == 1)
		*fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (redirect_type == 6)
		*fd = ft_atoi(file_name);
	invalid_fd = check_fd(*fd, file_name);
	if (invalid_fd)
		return (invalid_fd);
	return (0);
}

int	filename_to_fd(char *filenames, int redirect_type, t_redir *redir)
{
	int			i;
	char		*str;
	int			fd;
	static int	index_fd;

	init_to_zero(2, &fd, &i);
	if (redir->fd[0] == -1)
		index_fd = 0;
	while (filenames[i] && !is_redirect(filenames[i]))
		i++;
	str = ft_strdup(filenames);
	str[i] = 0;
	str = remove_quotes(str);
	redir->es = open_file(&fd, redirect_type, str);
	free(str);
	if (redir->es)
		return (1);
	redir->fd[index_fd++] = fd;
	exec_dup(redirect_type, fd);
	if (filenames[i])
	{
		redirect_type = get_redirect_and_skip(filenames, &i);
		filename_to_fd(&filenames[i], redirect_type, redir);
	}
	return (0);
}

char	**get_filenames(t_redir *redir, int index, int d, int redirect_type)
{
	int		i;
	char	**cmd;

	cmd = redir->cmd;
	i = index;
	while ((redir->cmd[d][i]) && is_redirect(redir->cmd[d][i]))
	{
		redirect_type += is_redirect(redir->cmd[d][i++]);
		redir->cmd[d][index] = '\0';
	}
	if (redir->cmd[d][i])
		filename_to_fd(&redir->cmd[d][i], redirect_type, redir);
	else
	{
		get_filenames(redir, 0, d + 1, redirect_type);
		cmd = delete_str(redir->cmd, d + 1);
	}
	return (cmd);
}

char	**ft_redirect(t_redir *redir)
{
	int	i;
	int	d;
	int	quote;

	i = -1;
	while (redir->cmd[++i])
	{
		d = -1;
		while (redir->cmd[i][++d])
		{
			if (is_redirect(redir->cmd[i][d]))
			{
				redir->cmd = get_filenames(redir, d, i, 0);
				if (!redir->cmd)
					return (NULL);
				if (ft_strlen(redir->cmd[i]) == 0)
					redir->cmd = delete_str(redir->cmd, i);
				return (ft_redirect(redir));
			}
			quote = isquote(redir->cmd[i][d]);
			if (quote)
				d = go_through_quote(redir->cmd[i], d, &quote);
		}
	}
	return (redir->cmd);
}
