#include "./libftp.h"

char	**str_list_dup(char **src_list)
{
	char **str_dup;
	int	i;

	i = 0;
	str_dup = calloc_str_list(strlen_list(src_list));
	if (!str_dup)
		return (NULL);
	while (src_list[i])
	{
		str_dup[i] = ft_strdup(src_list[i]);
		if (!str_dup[i])
			return (free_list_and_return_null(str_dup, i));
		i++;
	}
	return (str_dup);
}
