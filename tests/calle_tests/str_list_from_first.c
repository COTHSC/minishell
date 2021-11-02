#include <stdio.h>
#include "../../libs/libft/libft.h"
#include "../../libs/libft+/libftp.h"

int main(void )
{
	char **list;
	char ***p_list;

	list = ft_split("xHello xWorld", ' ');
	p_list = &list;
	//print_str_list(list, NULL);
	print_str_list(&(*p_list[1]), NULL);
	free_str_list(list, strlen_list(list));
	return (0);
}

	//list[0][1]
	//list[1][1]
	//printf("%s\n", &(p_list[0][1]));
