#include "libftp.h"

char **str_add(char **str_list, char *str_to_add)
{
	int	i;
	char **str_list_dup;
	int	list_size;

	i = 0;
	list_size = strlen_list(str_list);
	str_list_dup = calloc_str_list(list_size + 1);
	if (!str_list_dup)
		return (NULL);
	while (i < list_size)
	{
		str_list_dup[i] = ft_strdup(str_list[i]);
		if (!str_list_dup[i])
			return (free_list_and_return_null(str_list_dup, i));
		i++;
	}
	str_list_dup[i] = ft_strdup(str_to_add);
	if (!str_list_dup[i])
		return (free_list_and_return_null(str_list_dup, i));
	return (str_list_dup);
}
