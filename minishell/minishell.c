/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/04 17:54:43 by dgarizad         ###   ########.fr       */
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
		g_data.token1 = pipexsplit((g_data.input));
		if (strcmp((g_data.token1[0]), "exit") == 0) //THIS NEEDS CORRECTIONS,,,eat first spaces
			ft_exit();
		ft_check_expand();
		g_data.input_ex = ft_untoken();
		g_data.flags.token1 = 1;
		g_data.token2 = pipexsplit(g_data.input_ex);
		g_data.flags.token1 = 0;
		g_data.pipes = ft_split(g_data.input_ex, '|');
		printf("\nLIST OF COMMANDS:\n");
		print_token1(g_data.pipes);
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
