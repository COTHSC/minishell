/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:17:32 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 19:03:31 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_heredoc(char *s, int i)
{
	int		fd[2];
	char	*command;
	char	*test;
	char	*temp;

	if (!s[i + 2])
		return (s);
	command = ft_strndup(s, i);
	temp = make_heredocs(&s[i], fd);
	if (!temp)
	{
		free(command);
		return (s);
	}
	test = ft_strjoin(command, temp);
	free(command);
	free(temp);
	free(s);
	s = test;
	return (s);
}

char	*parse_line(char *s)
{
	int		i;
	int		quote;

	i = 1;
	while (s[i])
	{
		if (s[i - 1] == '<' && s[i] == '<')
			return (get_heredoc(s, i - 1));
		quote = isquote(s[i - 1]);
		if (quote)
		{
			i = go_through_quote(s, i - 1, &quote);
			if (s[i])
				i++;
		}
		if (s[i])
			i++;
	}
	return (s);
}

char	**parse_block(char **cmd_block)
{
	int		i;
	char	*sep;
	int		fd[2];
	char	**newblock;

	i = 0;
	if (!cmd_block)
		return (cmd_block);
	newblock = str_list_dup(cmd_block);
	free_str_list(cmd_block, strlen_list(cmd_block));
	while (newblock[i])
	{
		newblock[i] = parse_line(newblock[i]);
		if (end_is_heredoc(newblock[i]))
		{
			sep = get_sep(newblock[i + 1]);
			exec_heredoc(sep, fd);
			newblock[i + 1] = replace_del(newblock[i + 1], sep, fd[0]);
			free(sep);
		}
		i++;
	}
	return (newblock);
}
