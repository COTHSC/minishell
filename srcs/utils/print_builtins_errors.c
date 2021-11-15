#include "../../includes/minishell.h"

void	perror_invalid_option(char *builtin, char *options, char *valid_options)
{
	int	i;

	i = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": ", 2);
	ft_putchar_fd(options[0], 2);
	while (options[i])
	{
		if (!ft_strchr(valid_options, options[i]))
		{
			ft_putchar_fd(options[i], 2);
			break;
		}
		i++;
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("invalid option", 2);
	ft_putchar_fd('\n', 2);
}

void	perror_not_a_valid_identifier(char *identifier, char *builtin)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
}
