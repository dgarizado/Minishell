/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:48:53 by dgarizad          #+#    #+#             */
/*   Updated: 2022/11/30 22:52:03 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	j = 0;
	if (dstsize)
	{
		while (j < i && j < dstsize)
		{
			dst[j] = src [j];
			j++;
		}
		if (dstsize > i)
			dst[i] = 0;
		else
			dst[dstsize -1] = 0;
	}
	return (i);
}
