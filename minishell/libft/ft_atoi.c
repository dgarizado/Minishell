/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:04:12 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/06 15:03:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
//#include <stdio.h>

static int	ft_is_num(char str)
{
	int	flag;

	flag = 1;
	if (str < 48 || str > 57)
		flag = 0;
	return (flag);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	digit;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
	{
		str++;
	}
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			sign *= -1;
		str++;
	}
	while (ft_is_num(str[i]) == 1)
	{
		digit = str[i++] - '0';
		number = (number * 10) + digit;
	}
		number = number * sign;
	return (number);
}
