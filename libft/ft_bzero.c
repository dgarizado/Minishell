/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:10:04 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:02:17 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <strings.h>
//#include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		*((char *)(s + i)) = '\0';
		i++;
	}
}
