#include "builtins.h"

int	var_is_matching(char *var_to_compare, char *var_to_match)
{
	int		c_pos;
	char	*c_addr;
	int		max_len;
	int		sep;

	sep = '=';
	c_addr = ft_strchr(var_to_compare, sep);
	max_len = max_strlen(var_to_compare, var_to_match);
	if (!c_addr && ft_strncmp(var_to_compare, var_to_match, max_len) == 0)
		return (1);
	c_pos = c_addr - var_to_compare;
	if (c_pos == (long)ft_strlen(var_to_match)
		&& (ft_strnstr(var_to_compare, var_to_match, c_pos) - var_to_compare == 0))
		return (1);
	return (0);
}

int	count_match_in_var_list(char **var_list, char *var_to_match)
{
	int	nbr_of_match;
	int	i;
	int sep;

	i = 0;
	sep = '=';
	nbr_of_match = 0;
	while (var_list[i])
	{
		if (var_is_matching(var_list[i], var_to_match))
			nbr_of_match++;
		i++;
	}
	return (nbr_of_match);
}
