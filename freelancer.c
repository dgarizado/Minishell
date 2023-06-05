/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelancer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:03:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/05 18:41:49 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		free(arr[i++]);
		arr[i - 1] = NULL;
	}
	free(arr);
	return (0);
}

int freelancer(void)
{
	// printf(YELLOW"freelancer\n"RST_CLR""RST_CLR);
	// printf("freeing input %s : "YELLOW"%p\n"RST_CLR""RST_CLR, g_data.input, g_data.input);
	// printf("freeing tokenized lvl1 %p : "YELLOW"%s\n"RST_CLR""RST_CLR, g_data.token1[0], g_data.token1[0]);
	// printf("freeing input_ex %s : "YELLOW"%p\n"RST_CLR""RST_CLR, g_data.input_ex, g_data.input_ex);
	if (g_data.input != NULL)
	{
		free(g_data.input);
		g_data.input = NULL;
	}
	if (g_data.token1 != NULL)
	{
		ft_free_split(g_data.token1);
		g_data.token1 = NULL;
	}
	if (g_data.input_ex != NULL)
	{
		free(g_data.input_ex);
		g_data.input_ex = NULL;
	}
	// if (g_data.commands != NULL)
	// {
	// 	ft_free_split(g_data.commands);
	// 	g_data.commands = NULL;
	// }
	// if (g_data.tokenized_cmd != NULL)
	// {
	// 	ft_free_split(g_data.tokenized_cmd);
	// 	g_data.tokenized_cmd = NULL;
	// }

	return (0);
}