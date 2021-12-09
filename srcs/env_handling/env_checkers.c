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
	if (var)
		return (var[0] == 'x');
	else
		return (-1);
}

int	var_already_exist(char **var_list, char *var)
{
	if (match_var_name(var_list, var))
		return (1);
	else
		return (0);
}

int	has_valid_var_name(char *var)
{
	int		i;
	int		check_ret;
	char	**name_value_pair;

	name_value_pair = split_to_name_value_pair(var);
	i = 0;
	check_ret = 1;
	if (!name_value_pair[0][0])
		return (0);
	if (!ft_test_through_str(name_value_pair[0], &ft_isanywordchar))
		check_ret = 0;
	if (ft_isdigit(name_value_pair[0][0]))
		check_ret = 0;
	free_str_list(name_value_pair, strlen_list(name_value_pair));
	return (check_ret);
}
