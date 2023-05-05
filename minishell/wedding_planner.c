/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/05 18:35:00 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_count_pipes(void)
{
	int	i;

	i = 0;
	while (g_data.token1[i] != NULL)
	{
		if (strcmp(g_data.token1[i], "|") == 0)
		{
			printf("\nFound a felipe at:%d \n", i);
		}
		i++;
	}
	return (i);
}

int	wedding_planner(void)
{
	ft_count_pipes();	
	return (0);
}