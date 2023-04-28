/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:33:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:04:33 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
#include "libft.h"

static char	*ft_cat(char *dest, const char *src, size_t index)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(src))
	{
		dest[index] = src[i];
		index++;
		i++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;

	new_string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_string)
		return (NULL);
	new_string = ft_cat(new_string, s1, 0);
	new_string = ft_cat(new_string, s2, ft_strlen(s1));
	return (new_string);
}
