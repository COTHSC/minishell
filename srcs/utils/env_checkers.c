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

int	has_valid_identifier(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i] && var_name[i] != '=')	
	{
		if (!ft_isalnum(var_name[i]))
			return (0);
		i++;
	}
	if ((i == 0) && (var_name[i] == '='))
		return (0);
	else
		return (1);
}
