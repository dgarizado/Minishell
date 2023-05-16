/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:34:01 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:02:46 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*((char *)(dst + i)) = *((char *)(src + i));
		if ((char *)(src + i) == (void *)0)
			return (dst);
		i++;
	}
	return (dst);
}
