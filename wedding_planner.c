/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/23 20:51:49 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Counts the number of pipes in the input.
 * uses the tokenized1 version for an easy development.
 * @return int 
 */
int	ft_count_pipes(void)
{
	int	i;
	int pipes;
	
	i = 0;
	pipes = 0;
	while (g_data.token1[i] != NULL)
	{
		if (strcmp(g_data.token1[i], "|") == 0)
		{
			pipes++;
		}
		i++;
	}
	return (pipes);
}

char	*ft_join_pipes(int *i)
{
	char	*newstr;
	char	*aux;

	newstr = g_data.token1[*i];
	while (g_data.token1[(*i) + 1] != NULL)
	{
		aux = newstr;
		if (strcmp(g_data.token1[(*i) + 1], "|") == 0)
		{
			if (g_data.token1[(*i) + 1] == NULL)
				break;
			(*i) += 2;
			break ;
		}
		newstr = ft_join(aux, g_data.token1[(*i) + 1]);
		aux = NULL;
		free (aux);
		(*i)++;
	}
	return (newstr);
}

/**
 * @brief Counts pipes and allocates 
 * pipes + 2 strings (for NULL terminating and for the last command)
 * 
 * @return int 
 */
int	wedding_planner(void)
{
	//printf("\n----BEFORE SPECIALSPLIT YES '' INTO WEDDING PLANNER------\n%s\n", g_data.input_ex);
	g_data.flags.token1 = 0;
	g_data.commands = specialsplit(g_data.input_ex, '|');
	//write(1, "\n--------ARR INTO WEEDING PLANNER SPLIT INT '|' !-------\n",58); 
	//ft_printf_arr(g_data.commands);
	if (ft_arrlen(g_data.commands) > 1)
		exit(ft_pipex(g_data.commands));
	else
		exit(ft_program(g_data.commands[0]));
	return (0);
}
