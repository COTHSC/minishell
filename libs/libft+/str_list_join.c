#include "libftp.h"

char	**str_list_join(char **s1, char **s2)
{
	char	**ret_list;
	int		i;
	int		len1;
	int		len2;

	len1 = strlen_list(s1);
	len2 = strlen_list(s2);
	ret_list = calloc_str_list(len1 + len2 + 1);
	i = 0;
	while(ret_list && i < len1)
	{
		ret_list[i] = ft_strdup(s1[i]);
		if (!ret_list[i])
			return (free_list_and_return_null(ret_list, i));
		i++;
	}
	i = 0;
	while(ret_list && i < len2)
	{
		ret_list[len1 + i] = ft_strdup(s2[i]);
		if (!ret_list[len1 + i])
			return (free_list_and_return_null(ret_list, len1 + i));
		i++;
	}
	return (ret_list);
}
