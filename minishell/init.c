/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/01 18:46:45 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	operators(void)
{
	g_data.redirector[INFILE] = '<';
	//g_data.redirector[DELIMITER] = '<<';
	g_data.redirector[OUTFILE] = '>';
	//g_data.redirector[APPEND] = '>>';
	g_data.separator[PIPE] = '|';
	//data.separator[AND] = '&&';
	//data.separator[OR] = '||';
	return (0);
}
/**
 * @brief Main process wont execute commands. 
 * it reads the input and then forks.
 * 
 * @return int 
 */
int	init(void)
{
	ft_bzero(&g_data, sizeof(g_data));
	operators();
	while (1)
	{
		g_data.input = readline(PINK"mi"YELLOW"ni"BLUE"hell🐢"RST_CLR"$>");
		if (!(g_data.input))
			break ;
		add_history((g_data.input));
		rl_on_new_line();
		g_data.mainpid = fork();
		if (g_data.mainpid == 0)
			init_prompt();
		else
		{
			printf("\nBig daddy PID:%d\n", getpid());
			wait(&g_data.child_status);
			free((g_data.input));
			g_data.child_status = (WEXITSTATUS(g_data.child_status));
			if (g_data.child_status == 255)
				break ;
		}
	}
	return (0);
}
