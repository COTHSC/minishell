/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_declarations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:50:55 by jescully          #+#    #+#             */
/*   Updated: 2021/12/06 18:00:25 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	switch_declaration_on(char **args)
{
	int		i;
	int		declaration_switch;

	i = 0;
	declaration_switch = 1;
	while (args[i] && declaration_switch)
	{
		if (find_index_of_char(args[i], '=') < 1)
			declaration_switch = 0;
		if (!has_valid_var_name(args[i]))
			declaration_switch = 0;
		i++;
	}
	return (declaration_switch);
}

char	**delete_block(char **command_blocks, int index_block_to_del)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_str_list(strlen_list(command_blocks));
	if (!tmp)
		return (NULL);
	while (command_blocks[i])
	{
		if (i == index_block_to_del)
			j--;
		else
		{
			tmp[j] = ft_strdup(command_blocks[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
		i++;
	}
	return (tmp);
}

char	**remove_valid_declaration(char **command_blocks)
{
	char	**cleaned_cmds;
	char	**tmp;
	int		i;
	int		j;

	init_to_zero(2, &i, &j);
	cleaned_cmds = str_list_dup(command_blocks);
	while (command_blocks[i])
	{
		if ((find_index_of_char(command_blocks[i], '=') >= 1)
			&& has_valid_var_name(command_blocks[i]))
		{
			tmp = str_list_dup(cleaned_cmds);
			free_str_list(cleaned_cmds, strlen_list(cleaned_cmds));
			cleaned_cmds = delete_block(tmp, i - j);
			free_str_list(tmp, strlen_list(tmp));
			if (!cleaned_cmds)
				return (NULL);
			j++;
		}
		else
			return (cleaned_cmds);
		i++;
	}
	return (cleaned_cmds);
}

char	**parse_declaration(char **command_blocks)
{
	char	**cleaned_blocks;
	int		declaration_switch;

	declaration_switch = switch_declaration_on(command_blocks);
	if (declaration_switch == 0)
	{
		cleaned_blocks = remove_valid_declaration(command_blocks);
		free_str_list(command_blocks, strlen_list(command_blocks));
		return (cleaned_blocks);
	}
	else
	{
		check_and_alter_env(command_blocks, "d");
		cleaned_blocks = NULL;
		free_str_list(command_blocks, strlen_list(command_blocks));
		return (cleaned_blocks);
	}
}
