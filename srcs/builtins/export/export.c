/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:15:47 by calle             #+#    #+#             */
/*   Updated: 2021/10/25 12:23:25 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	**double_quoting_env_value(char **src)
{
	int		i;
	char	*equal_pos;
	char	**dest;
	int		dist;

	i = 0;
	dest = calloc_str_list(strlen_list(src));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		equal_pos = ft_strchr(src[i], '=');
		if (equal_pos)
		{
			dest[i] = malloc(sizeof(char) * (ft_strlen(src[i]) + 3));
			dist = equal_pos - src[i];
			ft_strlcpy(dest[i], src[i], dist + 2);
			dest[i][dist + 1] = '"';
			ft_strlcpy(&dest[i][dist + 2], &src[i][dist + 1], ft_strlen(&src[i][dist]));
			dest[i][ft_strlen(src[i]) + 1] = '"';
			dest[i][ft_strlen(src[i]) + 2] = 0;
		}
		i++;
	}
	return (dest);
}

int	display_entire_env_vars(char **env)
{
	char	**temp1;
	char	**temp2;

	temp1 = sort_str_list(env);
	temp2 = double_quoting_env_value(temp1);
	print_str_list(temp2, "declare -x ");
	if (temp1)
		free_str_list(temp1, strlen_list(temp1));
	if (temp2)
		free_str_list(temp2, strlen_list(temp2));
	return (EXIT_SUCCESS);
}

int	p_option_called(char *first_arg)
{
	if (ft_strncmp(first_arg, "-p", max_strlen(first_arg, "-p")) == 0)
		return (1);
	else
		return (0);
}

int	is_option(char *first_arg)
{
	return (*first_arg == '-');
}

void func ( void (*f)(int) );

char **str_add(char **str_list, char *str_to_add)
{
	int	i;
	char **str_list_dup;
	int	list_size;

	i = 0;
	list_size = strlen_list(str_list);
	str_list_dup = calloc_str_list(list_size + 1);
	while (i < list_size)
	{
		str_list_dup[i] = ft_strdup(str_list[i]);
		if (!str_list_dup[i])
		{
			free_str_list(str_list, i);
			return (NULL);
		}
		i++;
	}
	str_list_dup[i] = ft_strdup(str_to_add);
	if (!str_list_dup[i])
	{
		free_str_list(str_list, i);
		return (NULL);
	}
	return (str_list_dup);
}

int	add_vars_to_env(char **argv, char **env) 
{
	char **temp;
	int	i;
	
	i = 1;
	while (argv[i])
	{
		temp = str_add(env, argv[i]);
		if (!temp)
			return (EXIT_FAILURE);
		env = temp;
		//free(temp);
		i++;
	}
	//printf("index: %d -- argv[index] = %s\n", i, argv[i]);
	//print_str_list(env, NULL);
	return (EXIT_FAILURE);
}

int ft_export(int argc, char **argv, char **env)
{
	if (argc == 1 || (argc == 2 && p_option_called(argv[1])))
		return (display_entire_env_vars(env));
	if (argc == 2 && is_option(argv[1]) && !p_option_called(argv[1]))	
		return (EXIT_FAILURE);
	else
	{
		add_vars_to_env(argv, env);
		print_str_list(env, NULL);
		return (0);
	}
}
