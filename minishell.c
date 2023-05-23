/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/23 12:05:38 by vcereced         ###   ########.fr       */
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
		// ft_lexic((g_data.input));// MOVE TO MAIN TO AVOID EXECUTE CD, EXPORT, UNSET IN CHILD PROCESS
		//ft_parcerito();
		// printf(YELLOW"\nLIST OF TOKENS LEVEL1:\n"RST_CLR);
		// print_token1(g_data.token1);
		//printf(YELLOW"\nWEDDING PLANNER!:\n"RST_CLR);
		wedding_planner();
		//print_token1(g_data.commands);
		//printf(YELLOW"\nPROGRAM!:\n"RST_CLR);
		//printf("\ninput str:%s\n", g_data.input_ex);
		//HERE WE CALL PIPEX!!!
			//INSIDE PIPEX PROGRAM IS CALLED!
		//
		//ft_program(g_data.commands[0]);
		//printf(BLUE"\ninfiles:\n"RST_CLR);
		//print_token1(g_data.infiles);
		//printf(BLUE"\noutfiles:\n"RST_CLR);
		//print_token1(g_data.outfiles);
		//free(g_data.token1); //THIS IS NOT PROPERLY FREED. IS A SPLIT!
		//exit(0); //HERE WE DEVELOP HOW TO KILL THIS CHILD
	return (0);
}

//CHECKPOINT
int	main(int argc, char **argv, char **env)
{	
	argc = 0;
	argv = NULL;
	init(env);
	return (0);
}
