#include "./libftp.h"

char	**calloc_str_list(int size)
{
	char **str_list;

	str_list = (char **)ft_calloc(size, sizeof(char *));
	return (str_list);
}
