/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/07 18:05:04 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief Counts pipes and allocates 
 * pipes + 2 strings (for NULL terminating and for the last command)
 * 
 * @return int 
 */
int	wedding_planner(void)
{
	g_data.flags.token1 = 0;
	g_data.commands = specialsplit(g_data.input_ex, '|');
	free(g_data.input_ex);
	if (ft_arrlen(g_data.commands) > 1)
	{
		exit(ft_pipex(g_data.commands));
	}
	else
	{
		exit(ft_program(g_data.commands[0]));
	}
	return (0);
}
