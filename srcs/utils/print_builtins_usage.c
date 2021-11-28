#include "../../includes/minishell.h"

void	print_usage_export(void)
{
	ft_putstr_fd("export: usage: ", 2);
	ft_putstr_fd("export [name[=value] ...]", 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage_unset(void)
{
	ft_putstr_fd("unset: usage: ", 2);
	ft_putstr_fd("unset [name ...]", 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage_env(void)
{
	ft_putstr_fd("env: usage: ", 2);
	ft_putstr_fd("env", 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage_cd(void)
{
	ft_putstr_fd("cd: usage: ", 2);
	ft_putstr_fd("cd [dir]", 2);
	ft_putchar_fd('\n', 2);
}
