/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:54:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:04:04 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static long	ft_get_base(int n)
{
	unsigned long	j;
	int				i;

	j = 1;
	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		j *= 10;
		i++;
	}
	return (j / 10);
}

static char	*ft_get_pointer(long *ln, char *str)
{
	if (*ln < 0)
	{
		str = (char *)malloc(ft_count(*ln) + 2);
		*ln *= -1;
	}
	else
		str = (char *)malloc(ft_count(*ln) + 1);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	long		base;
	long		ln;
	int			i;
	char		*str;

	str = NULL;
	ln = n;
	str = ft_get_pointer(&ln, str);
	if (!str)
		return (NULL);
	base = ft_get_base(n);
	i = 0;
	if (n < 0)
		str[i++] = '-';
	while (base != 0)
	{
		str[i++] = (ln / base) + 48;
		ln %= base;
		base /= 10;
	}
	str[i] = '\0';
	return (str);
}
