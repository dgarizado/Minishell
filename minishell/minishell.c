/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/02 22:53:52 by dgarizad         ###   ########.fr       */
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

int	init_prompt(void)
{
	while (42)
	{
		ft_lexic((g_data.input));
		g_data.token1 = pipexsplit((g_data.input));
		if (strcmp((g_data.input), "exit") == 0) //THIS NEEDS CORRECTIONS,,,eat first spaces
			ft_exit();
		//print_token1(g_data.token1);
		ft_check_expand();
		print_token1(g_data.token1);
		free(g_data.token1);
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
