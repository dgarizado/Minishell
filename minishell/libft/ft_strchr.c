/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:45:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/05 19:59:01 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)(s + i));
	else
		return (0);
	return ((char *)s);
}

// int	main(void)
// {
// 	char	s[] = "AnitalavalatinA";
// 	char	c = 'l';
// 	printf("first occurrence: '%c' in '%s': '%s' : ",c,s, ft_strchr(s,c));
// 	return (0);
// }
