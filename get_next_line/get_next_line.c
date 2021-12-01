/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:30:17 by jescully          #+#    #+#             */
/*   Updated: 2021/12/01 19:30:18 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 100

static char	*cleaned_up_line(char *line)
{
	int			i;
	char		*clean_line;

	i = 0;
	if (!line || ft_strlen(line) == 0)
	{
		clean_line = (char *)malloc(1);
		clean_line[0] = '\0';
		return (clean_line);
	}
	while (line[i] && line[i] != '\n')
		i++;
	clean_line = (char *)(malloc(sizeof(char) * (i + 1)));
	if (!clean_line)
		return (NULL);
	ft_strlcpy(clean_line, line, i + 1);
	return (clean_line);
}

static char	*leftovers(char *available_string)
{
	static char	*new_string;

	if (!available_string || ft_strlen(available_string) == 0)
		return (NULL);
	if (!ft_strchr(available_string, '\n'))
	{
		free(available_string);
		return (NULL);
	}
	new_string = ft_strdup(ft_strchr(available_string, '\n') + 1);
	free(available_string);
	return (new_string);
}

static int	checkimp(char *bufstr, int const fd, char **line)
{
	if (fd < 0 || fd > 1024 || !bufstr || !line || BUFFER_SIZE <= 0)
	{
		if (bufstr)
			free(bufstr);
		line = NULL;
		return (0);
	}
	else
		return (1);
}

int	get_next_line(int const fd, char **line)
{
	static char	*available_string;
	char		*bufstr;
	int			bytes;

	bufstr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bufstr)
		return (-1);
	bytes = 1;
	if (!checkimp(bufstr, fd, line))
		return (-1);
	while (!ft_strchr(available_string, '\n') && bytes != 0)
	{
		if (get_str(bufstr, &available_string, fd, &bytes) == -1)
			return (-1);
	}
	free(bufstr);
	*line = cleaned_up_line(available_string);
	available_string = leftovers(available_string);
	if (available_string)
		bytes = not_a_ternary(bytes, available_string);
	return (bytes);
}
