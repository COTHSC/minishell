/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:17:32 by jescully          #+#    #+#             */
/*   Updated: 2021/12/08 19:13:08 by jescully         ###   ########.fr       */
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
	test = ft_strjoin(command, temp);
	free_strs_return_null(3, command, temp, s);
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

	i = 0;
	if (!cmd_block)
		return (cmd_block);
	while (cmd_block[i])
	{
		cmd_block[i] = parse_line(cmd_block[i]);
		if (end_is_heredoc(cmd_block[i]))
		{
			sep = get_sep(cmd_block[i + 1]);
			exec_heredoc(sep, fd);
			cmd_block[i + 1] = replace_del(cmd_block[i + 1], sep, fd[0]);
			free(sep);
		}
		i++;
	}
	return (cmd_block);
}
