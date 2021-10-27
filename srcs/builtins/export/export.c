/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:15:47 by calle             #+#    #+#             */
/*   Updated: 2021/10/27 14:10:14 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	*free_and_return_str_list(char **str_list, int nbr_str_alloc)
{
	free_str_list(str_list, nbr_str_alloc);
	return (NULL);
}

char	**str_list_dup(char **src_list)
{
	char **str_dup;
	int	i;

	i = 0;
	str_dup = calloc_str_list(strlen_list(src_list));
	if (!str_dup)
		return (NULL);
	while (src_list[i])
	{
		str_dup[i] = ft_strdup(src_list[i]);
		if (!str_dup[i])
			return (free_and_return_str_list(str_dup, i));
		i++;
	}
	return (str_dup);
}

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
			return (free_and_return_str_list(str_list_dup, i));
		i++;
	}
	str_list_dup[i] = ft_strdup(str_to_add);
	if (!str_list_dup[i])
		return (free_and_return_str_list(str_list_dup, i));
	return (str_list_dup);
}

char	**str_list_join(char **s1, char **s2)
{
	char	**ret_list;
	int		i;
	int		len1;
	int		len2;

	len1 = strlen_list(s1);
	len2 = strlen_list(s2);
	ret_list = calloc_str_list(len1 + len2);
	i = 0;
	while(ret_list && i < len1)
	{
		ret_list[i] = ft_strdup(s1[i]);
		if (!ret_list[i])
			return (free_and_return_str_list(ret_list, i));
		i++;
	}
	i = 0;
	while(ret_list && i < len2)
	{
		ret_list[len1 + i] = ft_strdup(s2[i]);
		if (!ret_list[len1 + i])
			return (free_and_return_str_list(ret_list, len1 + i));
		i++;
	}
	return (ret_list);
}

int ft_export(int argc, char **argv, char ***env)
{
	char	**tmp;

	if (argc == 1 || (argc == 2 && p_option_called(argv[1])))
		return (display_entire_env_vars(*env));
	if (argc == 2 && is_option(argv[1]) && !p_option_called(argv[1]))	
		return (EXIT_FAILURE);
	else
	{
		tmp = str_list_join(*env, argv + 1);
		if (!tmp)
			return (EXIT_FAILURE);
		free_str_list(*env, strlen_list(*env));
		*env = str_list_dup(tmp);
		free_str_list(tmp, strlen_list(tmp));
		return (0);
	}
}
