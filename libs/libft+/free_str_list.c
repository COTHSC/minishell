#include "./libftp.h"

void	free_str_list(char **str_list, int	size_to_free)
{
	int	i;

	i = 0;
	while (i < size_to_free && str_list[i])
	{
		free(str_list[i]);
		i++;
	}
}
