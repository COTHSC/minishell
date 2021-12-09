/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:08:08 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 17:08:09 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes_list(char **command_block)
{
	int		i;
	char	*temp;

	i = 0;
	while (command_block[i])
	{
		temp = remove_quotes(command_block[i]);
		command_block[i] = temp;
		i++;
	}
}
