/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/06 18:32:23 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	add_history_aux(char *input)
{
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
/**
 * @brief check if run ft_program in main process to save the changes of path and env.
 */
int check_to_exe(void)
{
	if (ft_check_exe() == 0 && ft_check_pipes() == 1 && g_data.flags.concurrency == 0)
	{
		return (0);
	}
	return (1);
}

void	ctrld(void)
{
	printf("\033[F\033[K"PROMPT"exit\n");
	ft_exit();
}

void ft_run(void)
{
	add_history_aux(g_data.input);
	g_data.flag = ft_lexic();
	if (g_data.flag == 0 && check_to_exe() == 0)
	{
		g_data.flag = ft_program(g_data.input_ex);
		g_data.child_status = g_data.flag;
	}
	else if (g_data.flag == 0)
	{
		g_data.father = 1;
		g_data.child_pid = fork();
		if (g_data.child_pid == 0)
		{
			set_signals(0);
			wedding_planner();
		}
	}
	waitpid(g_data.child_pid, &g_data.child_status, 0);
	if (WIFEXITED(g_data.child_status))
		g_data.child_status = WEXITSTATUS(g_data.child_status);
}

/**
 * @brief Main process wont execute commands. 
 * it reads the input and then forks.
 * @return int 
 */
int	init(void)
{
	while (42)
	{
		g_data.input = readline(PROMPT);
		if (!g_data.input)
			ctrld();
		if (g_data.input[0] != '\0')
		{
			ft_run();
		}
		freelancer();
		system("leaks minishell");
		g_data.flags.concurrency = 0;
		g_data.father = 0;
		g_data.flags.free_expanded = 0;
	}
	return (EXIT_SUCCESS);
}

