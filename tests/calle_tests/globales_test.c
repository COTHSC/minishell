#include <stdio.h>
#include "../../libs/libft/libft.h"

int	g_number;
char **g_test;

void	increase_number_by_one( int *number )
{
	(*number)++;
}

void	alter_list(char **list)
{
	free(list[0]);
	list[0] = ft_strdup("Hell");
}

void	alter_test( void )
{
	free(g_test[0]);
	list[0] = ft_strdup("Hell");
}

int	main(void)
{
	{
		//g_number = 0;

		//printf("g_number = %d\n" , g_number);
		//increase_number_by_one( &g_number );	
		//printf("g_number = %d\n" , g_number);
	}
	{
		g_test = ft_split("Hello World", ' ');
		printf("g_test = %s\n" , g_test[0]);
		printf("g_test = %s\n" , g_test[1]);
		alter_list( g_test );	
		printf("g_test = %s\n" , g_test[0]);
		printf("g_test = %s\n" , g_test[1]);
		free(g_test[0]);
		free(g_test[1]);
		free(g_test);
	}
	return (0);
}
