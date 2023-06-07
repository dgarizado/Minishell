/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_index_chr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:49:20 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/07 16:36:58 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Iter the string to find the char c. when find return n_byte.
 * @param s 
 * @param c 
 * @return int 0 when not appear. when appear return n_byte. when c == '\0 
 * return n_byte.
 * 
 */
int	ft_str_index_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i +1);
		i++;
	}
	if (c == 0)
		return (i +1);
	else
		return (0);
}
