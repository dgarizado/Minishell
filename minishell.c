/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/31 19:05:25 by dgarizad         ###   ########.fr       */
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
int	init_prompt_subps(void)
{
	wedding_planner();
	return (0);
}

void sigint_handler_child(int sig) 
{
	if (sig == SIGQUIT)
		sig = 3;
	if (g_data.child_pid == 0)
		exit(127);
}

void sigint_handler(int sig) 
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		waitpid(g_data.child_pid, &g_data.child_status, WUNTRACED);
				if (WIFEXITED(g_data.child_status))
					g_data.child_status = WEXITSTATUS(g_data.child_status);
	}
	if (sig == SIGQUIT)
		sig = 3;
}


void set_signals(int n)
{
	struct sigaction sa;

    sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
    sa.sa_flags = 0;
	if (n != 0)
	{
		sa.sa_handler = sigint_handler;
		if (sigaction(SIGINT, &sa, NULL) == -1)
        	perror("Error al configurar el manejador de señal");
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			perror("Error al configurar el manejador de señal");
	}
	if (n == 0)
	{
		 sa.sa_handler = sigint_handler_child;
		if (sigaction(SIGINT, &sa, NULL) == -1)
        	perror("Error al configurar el manejador de señal");
	}
	
}

//CHECKPOINT
int	main(int argc, char **argv ,char **env)
{	
	argc = 0;
	argv = NULL;
	ft_bzero(&g_data, sizeof(g_data));
	g_data.original_std_out = dup(STDOUT_FILENO);
	g_data.original_std_in = dup(STDIN_FILENO);
	g_data.env = env;
	set_signals(1);
	init();
	return (0);
}
