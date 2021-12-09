#include "../../includes/minishell.h"

void	print_minishell_error(int error, char *cmd, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error), 2);
	ft_putstr_fd("\n", 2);
}

void	print_file_error(int error, char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	if (filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(error), 2);
	ft_putstr_fd("\n", 2);
}

void	print_cmd_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
}
