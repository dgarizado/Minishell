/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:29 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/24 15:03:43 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	ft_error(char *err)
{
	ft_putstr_fd(err, 2);
	exit(errno);
}

/**
 * @brief Replace with a space the specific characters from i 
 * to j of the str.
 * 
 * @param i 
 * @param j 
 * @param str 
 * @return int 
 */
int	delete_str(int i, int j, char *str)
{
	while (i <= j && str[i] != '\0')
	{
		str[i] = ' ';
		i++;
	}
	return (0);
}
