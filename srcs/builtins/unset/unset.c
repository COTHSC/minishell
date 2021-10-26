#include "../builtins.h"

int		count_match_till_char(char **str_list, char *str_to_match, int c)
{
	int	nbr_of_match;
	int	i;
	int	c_pos;

	i = 0;
	nbr_of_match = 0;
	while (str_list[i])
	{
		c_pos = ft_strchr(str_list[i], c) - str_list[i];
		if (ft_strchr(str_list[i], '=') - str_list[i] == (long)ft_strlen(str_to_match)	
			&& (ft_strnstr(str_list[i], str_to_match, c_pos) - str_list[i] == 0))
			nbr_of_match++;
		i++;
	}
	return (nbr_of_match);
}

char	**str_delete(char **str_list, char *str_to_del, int nb_to_del)
{
	int	i;
	int j;
	char **tmp;
	int	c_pos;

	i = -1;
	j = 0;
	tmp = calloc_str_list(strlen_list(str_list) - nb_to_del);
	if (!tmp)
		return (NULL);
	while (str_list[++i])
	{
		c_pos = ft_strchr(str_list[i], c_pos) - str_list[i];
		if (ft_strchr(str_list[i], '=') - str_list[i] == (long)ft_strlen(str_to_del)	
			&& ft_strnstr(str_list[i], str_to_del, c_pos) - str_list[i] == 0)
			j--;
		else
		{
			tmp[j] = ft_strdup(str_list[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
	}
	return (tmp);
}

int	delete_element_from_env(char ***env, char **argv)
{
	int	i;
	char **tmp;
	int	count_matches;

	i = 1;
	while (argv[i])
	{
		count_matches = count_match_till_char(*env, argv[i], '='); 
		if (count_matches)
		{
			tmp = str_delete(*env, argv[i], count_matches);
			if (!tmp)
				return (EXIT_FAILURE);
			free_str_list(*env, strlen_list(*env));
			*env = str_list_dup(tmp);
			if (!tmp)
				return (EXIT_FAILURE);
			free_str_list(tmp, strlen_list(tmp));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_unset(int argc, char **argv, char ***env)
{
	(void)argc;
	(void)argv;

	if (argc == 1)
		return (EXIT_SUCCESS);
	else
		return (delete_element_from_env(env, argv));
}
