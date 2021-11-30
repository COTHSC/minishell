/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:40:48 by jescully          #+#    #+#             */
/*   Updated: 2021/11/30 16:14:33 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_iswhitespace(int c)
{
   if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
       return (1);
   else
       return (0);
}
