/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/17 21:06:18 by dgarizad         ###   ########.fr       */
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
		printf(YELLOW"\nLIST OF TOKENS LEVEL1:\n"RST_CLR);
		print_token1(g_data.token1);
		printf(YELLOW"\nWEDDING PLANNER!:\n"RST_CLR);
		wedding_planner();
		print_token1(g_data.commands);
		printf("\ninput str:%s\n", g_data.input_ex);
		ft_program(g_data.pipes[0]);
		free(g_data.token1); //THIS IS NOT PROPERLY FREED. IS A SPLIT!
		exit(0); //HERE WE DEVELOP HOW TO KILL THIS CHILD
	}
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
