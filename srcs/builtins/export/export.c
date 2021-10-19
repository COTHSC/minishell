/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:15:47 by calle             #+#    #+#             */
/*   Updated: 2021/10/19 19:28:59 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/libft/libft.h"
#include <stdio.h>

//char **stradd(char **str_tab, char *new_str)
//{
//	char	**temp;
//	int		str_tab_len;
//	int		str_new_str;
//
//	temp = malloc(
//}

char	**max_strlen(const char *s1, const char *s2)
{
	int len1;
	int len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1 - len2);
	else
		return (len2 - len1);
}

int	is_not_in_str_list(char **str_list, char *str)
{
	int	i;

	i = 0;
	while (str_list[i])
	{
		if (!ft_strncmp(str_list[i], str, max_strlen(str_list[i], str)));
			return (0);
		i++;
	}
	return (1);
}

int		strlen_list(const char **str_list)
{
	int	i;

	i = 0;
	while (str_list[i])
		i++;
	return (i);
}

char	**calloc_str_list(int size)
{
	int	i;
	char **str_list;

	i = 0;
	while (i < size)
	{
		str_list = (char *)ft_calloc(1, sizeof(char));	
		i++;
	}
	return (str_list);
}

char **sort_str_list(char **str_list)
{
	char	**temp;
	int		i;
	int		head;
	int		max;
	int		smallest;

	head = 0
	temp = calloc_str_list(strlen_list(str_list));
	while (str_list[head])
	{
		i = head;
		while (str_list[i])
		{
			max = max_strlen(temp[head], str_list[i]);
			if (ft_strncmp(temp[head], str_list[i], max) > 0)	
			{
				if (is_not_in_str_list(temp, str_list[i]))
				{
					free(temp[head]);
					temp[head] = ft_strdup(str_list[i])
				}
			}
			i++;
		}
		temp[head] = ft_strdup(str_list[smallest]
		head++;
	}
	return (temp);
}

int	main(int argc, char **argv, char **env)
{
	char *temp;
	int	i;

	if (argc != 2)
		return (EXIT_FAILURE);
	temp = getenv(argv[1]);
	if (!temp)
		return (EXIT_FAILURE);
	i = -1;
	while (temp[++i])
	{
		printf("before: %c\n", temp[i]);
		temp[i] = '0';
		printf("after: %c\n", temp[i]);
	}
	printf("recall: %s\n", getenv(argv[1]));
	return (EXIT_SUCCESS);
}
