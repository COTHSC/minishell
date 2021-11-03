#include <stdio.h>
#include "../../libs/libft/libft.h"
#include "../../libs/libft+/libftp.h"

char **g_env;

void	print_my_list(char **my_list)
{
    int i = 0;
    while (my_list[i])
    {
        printf("%s\n", my_list[i]);
        i++;
    }
}

char **env_selector(int position_selector)
{
	char	**selection;
	int		i;

	selection = calloc_str_list(strlen_list(g_env));
	i = 0;
	while (g_env[i])
	{
		selection[i] = ft_strdup(g_env[i] + position_selector);
		i++;
	}
	return (selection);
}

void	alter_env(int pos_to_alter, char *replace)
{
	free(g_env[pos_to_alter]);
	g_env[pos_to_alter] = ft_strdup(replace);
}

int main(void )
{
	{
		//print env without flag
		char **carved_env;

		g_env = ft_split("xHello xWorld", ' ');
		carved_env = env_selector(1);
		print_my_list(carved_env);
		free_str_list(carved_env, strlen_list(carved_env));
		free_str_list(g_env, strlen_list(g_env));
	}
	{
		//alter an element in environnement base on matching var 
		char **carved_env;

		g_env = ft_split("xHello xWorld", ' ');
		carved_env = env_selector(1);
		if (ft_strncmp(carved_env[0], "Hello", 5) == 0)
			alter_env(0, "xYATTA");
		print_my_list(g_env);
		free_str_list(carved_env, strlen_list(carved_env));
		free_str_list(g_env, strlen_list(g_env));
	}
	//char ***p_list;
//	p_list = &list;
   // int i = 0;
   // i = 0;
   // while (list[i])
   // {
   //     printf("%s\n", (*(list + i) + 1));
   //     i++;
   // }
//    i = 0;
//    while ((*p_list + i))
//    {
//        printf("%s\n", *(*p_list + i) + 1);
//        i++;
//    }
    //while (p_list[0][i])
    //{
    //    printf("%s\n", &p_list[0][i][1]);
    //    i++;
    //}
    //i = 0;
    //while (list[i])
    //{
    //    printf("%s\n", &list[i][1]);
    //    i++;
    //}
	//print_my_list((&p_list[0][1]));

	//print_str_list(list, NULL);
//	print_str_list(&(*p_list[1]), NULL);
	return (0);
}

	//list[0][1]
	//list[1][1]
	//printf("%s\n", &(p_list[0][1]));
