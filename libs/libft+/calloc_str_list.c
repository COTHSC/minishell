#include "./libftp.h"

char	**calloc_str_list(int size)
{
	char **str_list;

	str_list = (char **)ft_calloc(size + 1, sizeof(char *));
	return (str_list);
}
