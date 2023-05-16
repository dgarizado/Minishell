/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:45:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/04 22:32:53 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

/**
 * @brief Search a character in a string. 
 * if the char is in the string, returns the pointer to the first 
 * ocurrence.
 * @param s 
 * @param c 
 * @return char* 
 */
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
