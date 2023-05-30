/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/30 17:12:54 by dgarizad         ###   ########.fr       */
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
 * @brief Child process that performs the ft_program.
 * 
 * @return int 
 */
//CHECKPOIINT
int	init_prompt(void)
{
	wedding_planner();
	return (0);
}

//CHECKPOINT
int	main(int argc, char **argv, char **env)
{	
	argc = 0;
	argv = NULL;
	printf(RED"Welcome to minishell: int is %zu:  . int* is: %zu \n"RST_CLR, sizeof(int), sizeof(int*));
	init(env);
	
	return (0);
}
