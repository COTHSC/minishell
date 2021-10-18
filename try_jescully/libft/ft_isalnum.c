/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:43:32 by jescully          #+#    #+#             */
/*   Updated: 2020/12/01 17:22:20 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isalphaa(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

static int	ft_isdigitt(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalphaa(c) || ft_isdigitt(c))
		return (1);
	else
		return (0);
}
