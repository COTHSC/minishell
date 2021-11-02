#include "./libftp.h"

int		strlen_list(char **str_list)
{
	int	i;

	i = 0;
	while (str_list[i])
		i++;
	return (i);
}
