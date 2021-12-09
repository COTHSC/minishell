/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:03:35 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 19:44:39 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*try_paths(char **paths, char *command)
{
	int		d;
	char	*path_bits;
	char	*path;

	d = -1;
	while (paths[++d])
	{
		path_bits = ft_strjoin(paths[d], "/");
		path = ft_strjoin(path_bits, command);
		free(path_bits);
		if (access(path, F_OK) == 0)
		{
			d = 0;
			while (paths[d])
				free(paths[d++]);
			free(paths);
			return (path);
		}
		free(path);
	}
	d = 0;
	while (paths[d])
		free(paths[d++]);
	free(paths);
	return (NULL);
}

int	builtin_finder(char *name)
{
	static char	*builtin_lookup[7];
	int			i;

	builtin_lookup[0] = "cd";
	builtin_lookup[1] = "pwd";
	builtin_lookup[2] = "exit";
	builtin_lookup[3] = "export";
	builtin_lookup[4] = "env";
	builtin_lookup[5] = "unset";
	builtin_lookup[6] = "echo";
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(name, builtin_lookup[i], ft_strlen(name)) == 0 \
				&& ft_strlen(name) == ft_strlen(builtin_lookup[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_path(char **command_block)
{
	char	**paths;
	int		d;
	char	*path;
	char	*check_ret;

	path = NULL;
	check_ret = ft_getenv("PATH", 'd');
	if (check_ret)
	{
		paths = ft_split(check_ret, ':');
		path = try_paths(paths, command_block[0]);
	}
	if (!path)
		if (access(command_block[0], F_OK) == 0)
			return (command_block[0]);
	if (!path)
	{
		d = 0;
		print_cmd_error(command_block[0]);
		while (command_block[d])
			free(command_block[d++]);
		free(command_block);
		exit(127);
	}
	return (path);
}
