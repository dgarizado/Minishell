/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/06 16:46:23 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	add_history_aux(char *input)
{
	// char	*tmp;

	// tmp = ft_strtrim(input, " ");
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
	//free(tmp);
}
/**
 * @brief check if run ft_program in main process to save the changes of path and env.
 * 
 */
int check_to_exe(void)
{
	// printf(YELLOW"stills token1: %p, '%s'\n"RST_CLR, g_data.token1, g_data.token1[0]);
	if (ft_check_exe() == 0 && ft_check_pipes() == 1 && g_data.flags.concurrency == 0)// EXE IN GENESIS
	{
		return (0);
		//status = ft_program(g_data.input_ex);
		//return (status);
	}
	return (1);
}

int init_prompt_current_ps(void)
{
	return (ft_program(g_data.input_ex));
}

void	ctrld(void)
{
	printf("\033[F\033[K"PROMPT"exit\n");
	printf("PRESSED CTRL-D! pointer input: %p\n", g_data.input);
	ft_exit();
}

/**
 * @brief Main process wont execute commands. 
 * it reads the input and then forks.
 * 
 * @return int 
 */
int	init(void)
{
	while (42)
	{
		g_data.input = readline(PROMPT);
		// printf(YELLOW"input: %p, %s\n"RST_CLR, g_data.input, g_data.input);
		if (!g_data.input)
			ctrld();
		if (g_data.input[0] != '\0')
		{
			add_history_aux(g_data.input);
			g_data.flag = ft_lexic();
			// printf(PINK"Input ex: '%s', %p\n"RST_CLR, g_data.input_ex, g_data.input_ex);
			//printf(YELLOW"still token1: %p, %s\n"RST_CLR, g_data.token1, g_data.token1[0]);
			if (g_data.flag == 0 && check_to_exe() == 0)
			{
				g_data.flag = init_prompt_current_ps();
				g_data.child_status = g_data.flag;
			}
			else if (g_data.flag == 0)
			{
				//printf(GREEN"ENTERED ALSO HERE\n"RST_CLR".\n"RST_CLR);
				g_data.father = 1;
				g_data.child_pid = fork();
				if (g_data.child_pid == 0)
				{
					set_signals(0);
					init_prompt_subps();
				}
			}
			waitpid(g_data.child_pid, &g_data.child_status, 0);
			if (WIFEXITED(g_data.child_status))
				g_data.child_status = WEXITSTATUS(g_data.child_status);
			//printf("\n:%d\n", g_data.child_status);
			g_data.father = 0;
			g_data.flags.concurrency = 0;
			//printf(RED"env array: %p\n"RST_CLR"\n"RST_CLR, g_data.env);
		}
		freelancer();
		system("leaks minishell");
		g_data.flags.free_expanded = 0;
	}
	return (EXIT_SUCCESS);
}
//CHECKPOINT!!!!
