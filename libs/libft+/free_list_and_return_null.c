#include "libftp.h"

void	*free_list_and_return_null(char **str_list, int nbr_str_alloc)
{
	free_str_list(str_list, nbr_str_alloc);
	return (NULL);
}
