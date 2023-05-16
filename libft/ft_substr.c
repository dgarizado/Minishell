/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:25:24 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/02 18:35:27 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief Receives a string, a starting point and the amount 
 * of chars to be copied from the starting point. 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*substring;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (NULL);
	substring = ft_memcpy(substring, &s[start], len);
	substring[len] = '\0';
	return (substring);
}
