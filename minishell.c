/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/17 20:05:36 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int	print_token1(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		printf("\n%s\n", str[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Child process that performs the
 * 
 * @return int 
 */
int	init_prompt(void)
{
	while (42)
	{
		ft_lexic((g_data.input));
		ft_parcerito();
		printf("\nLIST OF TOKENS LEVEL1:\n");
		print_token1(g_data.token1);
		printf("\nWEDDING PLANNER!:\n");
		wedding_planner();
		print_token1(g_data.commands);
		ft_program(g_data.pipes[0]);
		free(g_data.token1); //THIS IS NOT PROPERLY FREED. IS A SPLIT!
		exit(0); //HERE WE DEVELOP HOW TO KILL THIS CHILD
	}
	return (0);
}

//CHECKPOINT
int	main(void)
{	
	init();
	return (0);
}
