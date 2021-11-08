#include "../../includes/minishell.h"

char	*extract_value(char *var)
{
	char	sep;

	sep = '=';
	if (ft_strchr(var, sep))
		return (ft_strchr(var, sep) + 1);
	else
		return (NULL);
}

int	var_has_value(char *var)
{
	if (extract_value(var))
		return (1);
	else
		return (0);
}

int	var_is_exported(char *var)
{
	return (var[0] == 'x');
}

int	var_already_exist(char **var_list, char *var)
{
	if (match_var_name(var_list, var))
		return (1);
	else
		return (0);
}

void	change_flag(char **var, char flag)
{
	*var[0] = flag;
}
