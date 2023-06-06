/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/06 20:52:15 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	add_history_aux(char *input)
{
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}


static void	ctrld(void)
{
	printf("\033[F\033[K"PROMPT"exit\n");
	ft_exit();
}

static void ft_run(void)
{
	int flag;

	flag = 0;
	add_history_aux(g_data.input);
	flag = ft_lexic();
	if (flag == 0 && check_to_exe() == 0)
	{
		flag = ft_program(g_data.input_ex);
		g_data.child_status = flag;
	}
	else if (flag == 0)
	{
		g_data.flags.father = 1;
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
			g_data.flags.concurrency = 0;
			g_data.flags.father = 0;
		}
		freelancer();
		//system("leaks minishell");
		g_data.flags.free_expanded = 0;
	}
	return (EXIT_SUCCESS);
}

