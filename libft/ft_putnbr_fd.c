/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:37:31 by dgarizad          #+#    #+#             */
/*   Updated: 2022/12/08 17:14:57 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr(long nb, int fd)
{
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}	
	if (nb / 10 != 0)
	{
		ft_putnbr(nb / 10, fd);
	}
	ft_putchar((nb % 10) + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	ln = n;
	ft_putnbr(ln, fd);
}
