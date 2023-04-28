/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:31:20 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:04:49 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
// #include <string.h>
#include "libft.h"

static size_t	ft_cmp(const char *s1, const char*s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s2[i] != 0 && i < n)
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (*needle == haystack[i])
		{
			if (ft_cmp(&haystack[i], needle, len - i) == 1 \
			&& (ft_strlen(needle) <= len - i))
			{
				return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (0);
}
