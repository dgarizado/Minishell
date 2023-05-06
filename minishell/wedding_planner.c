/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/06 02:07:32 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Counts the number of pipes in the input.
 * uses the tokenized1 version for an easy development.
 * @return int 
 */
static int	ft_count_pipes(void)
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
	int	wd;
	int	i; 
	int j;
	
	g_data.pipes_nbr = ft_count_pipes();	
	g_data.commands = (char **)ft_calloc(g_data.pipes_nbr + 2, sizeof(char*)); //NEEDS FREEDOM
	if (!g_data.commands)
		return (1);
	wd = 0;
	j = 0;
	i = 0;
	while(wd < g_data.pipes_nbr +1)
	{
		g_data.commands[wd] = ft_join_pipes(&i);
		wd++;
	}
	return (0);
}