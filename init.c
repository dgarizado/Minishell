/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/01 20:32:33 by dgarizad         ###   ########.fr       */
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
	if (ft_check_exe() == 0 && ft_check_pipes() == 1)// EXE IN GENESIS
	{
		return (0);
		//status = ft_program(g_data.input_ex);
		//return (status);
	}
	return (1);
}

int init_prompt_current_ps()
{
	return (ft_program(g_data.input_ex));
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
		if (!g_data.input)
		{
			printf("\033[F\033[K"PROMPT"exit\n");
			ft_exit();
		}
		if (g_data.input[0] != '\0')
		{
			g_data.flag = ft_lexic();
			add_history_aux(g_data.input);
			if (g_data.flag == 0 && check_to_exe() == 0)
			{
				g_data.flag = init_prompt_current_ps();
				g_data.child_status = g_data.flag;
			}
			else if (g_data.flag == 0)
			{
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
			printf("\n:%d\n", g_data.child_status);
			g_data.flags.concurrency = 0;
			free((g_data.input));
		}
	}
	return (EXIT_SUCCESS);
}
