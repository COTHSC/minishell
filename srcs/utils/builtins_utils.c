#include "../builtins/builtins.h"

int	var_name_is_matching(char *var_to_compare, char *var_to_match)
{
	int		c_pos;
	char	*c_addr;
	int		max_len;
	int		sep;

	sep = '=';
	c_addr = ft_strchr(var_to_compare, sep); // var value exist ?
	max_len = max_strlen(var_to_compare, var_to_match);
	if (!c_addr && ft_strncmp(var_to_compare, var_to_match, max_len) == 0)
		return (1);
	c_pos = c_addr - var_to_compare;
	if (c_pos == (long)ft_strlen(var_to_match)
		&& (ft_strnstr(var_to_compare, var_to_match, c_pos) - var_to_compare == 0))
		return (1);
	return (0);
}

char	**match_var_name(char **var_list, char *var_to_match)
{
	int	i;
	int sep;

	i = 0;
	sep = '=';
	while (var_list[i])
	{
		if (var_name_is_matching(var_list[i], var_to_match))
			return (&var_list[i]);
		i++;
	}
	return (NULL);
}

char	*extract_value(char *var)
{
	char	sep;

	sep = '=';
	return (ft_strchr(var, sep) + 1);
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
