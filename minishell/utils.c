/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:29 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/01 16:23:04 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	ft_error(char *err)
{
	ft_putstr_fd(err, 2);
	exit(errno);
}

// int	ft_check_tokens(void)
// {
	
// 	return (0);
// }
