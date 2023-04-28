/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:25:39 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:05:03 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	len;

	if (!s1 || !set)
		return (0);
	while (s1[0] != '\0' && ft_strchr(set, s1[0]))
			s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
