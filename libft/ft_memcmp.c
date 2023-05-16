/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:57:57 by dgarizad          #+#    #+#             */
/*   Updated: 2022/12/01 18:11:52 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_compare(unsigned char s1, unsigned char s2)
{
	int	result;

	result = s1 - s2;
	return (result);
}

int	ft_memcmp(const void *s1, const void *s2, unsigned int n)
{
	unsigned int	i;
	int				result;

	i = 0;
	result = 0;
	while (i < n)
	{
		if (*(char *)(s1 + i) != *(char *)(s2 + i))
		{
			result = ft_compare(*(char *)(s1 + i), *(char *)(s2 + i));
			break ;
		}
		i++;
	}
	return (result);
}
