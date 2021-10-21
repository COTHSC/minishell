/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:46:59 by calle             #+#    #+#             */
/*   Updated: 2021/10/20 18:44:55 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTP_H
# define LIBFTP_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

int		ft_iswhitespace(char c);
void	free_str_list(char **str_list, int	size_to_free);
int		is_not_in_str_list(char **str_list, char *str);
int		max_strlen(const char *s1, const char *s2);
char	**sort_str_list(char **list);
void	print_str_list(char **str_list, char *print_before_list);
int		strlen_list(char **str_list);
char	**calloc_str_list(int size);

#endif
