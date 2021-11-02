#include <stdio.h>
#include "../../libs/libft/libft.h"
#include "../../libs/libft+/libftp.h"

void	print_my_list(char **my_list)
{
    int i = 0;
    while (my_list[i])
    {
        printf("%s\n", my_list[i]);
        i++;
    }
}

int main(void )
{
	char **list;
	char ***p_list;
    int i = 0;

	list = ft_split("xHello xWorld", ' ');
	p_list = &list;
    while (p_list[0][i])
    {
        printf("%s\n", &p_list[0][i][1]);
        i++;
    }
    i = 0;
    while (list[i])
    {
        printf("%s\n", &list[i][1]);
        i++;
    }
	print_my_list((&list[0][1]));

	//print_str_list(list, NULL);
//	print_str_list(&(*p_list[1]), NULL);
	return (0);
}

	//list[0][1]
	//list[1][1]
	//printf("%s\n", &(p_list[0][1]));
