/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:48:42 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/05 17:24:06 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *arr, int *i, int *len)
{
	int	n;

	n = 1;
	while (arr[n])
	{
		if (ft_strncmp(&(arr[n]), "n", 1))
		{
			*i = 1;
			return (0);
		}
		n++;
	}
	*len = --(*len);
	*i = 2;
	return (1);
}

static int	is_flag_n(char **arr, int *i, int *len)
{
	if (ft_strncmp(arr[1], "-", 1))
	{
		*i = 1;
		return (0);
	}
	else
		return (check_flag(arr[1], i, len));
}

int	ft_echo(char **arr)
{
	int	len;
	int	i;
	int	flag;

	flag = 0;
	if (!arr || !(*arr))
		return(errno);
	if (arr[1])
	{
		len = 0;
		while (arr[len])
			len++;
		flag = is_flag_n(arr, &i, &len);
		while (--len > 0)
		{
			write(1, arr[i], ft_strlen(arr[i]));
			if (len > 1)
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return(EXIT_SUCCESS);
}
