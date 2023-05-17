/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:14:50 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/16 20:34:06 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	ft_count_del(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (*s && *s != c)
		count++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_array_gen(char const *s, char c, char **new_array)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c)
			{
				j++;
				s++;
			}
			new_array[i++] = ft_substr(s - j, 0, j);
			if (!new_array[i - 1])
				return (ft_abort(new_array, i));
		}
		else
			s++;
	}
	return (new_array);
}

char	**ft_split(char const *s, char c)
{
	char			**new_array;

	new_array = (char **)ft_calloc((ft_count_del(s, c) + 1), sizeof (char *));
	if (!new_array)
		return (NULL);
	new_array = ft_array_gen(s, c, new_array);
	return (new_array);
}
