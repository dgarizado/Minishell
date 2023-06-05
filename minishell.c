/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/05 20:28:06 by dgarizad         ###   ########.fr       */
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
	sig = 0;
	//printf("HA MUERTO UN HIJO!\n");
//	if (g_data.child_pid == 0)
		exit(127);
}

void sigint_handler(int sig) 
{
	sig = 0;
	if (g_data.father == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n\033[F\033[K"PROMPT"\n");
		rl_redisplay();
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	waitpid(g_data.child_pid, &g_data.child_status, WUNTRACED);
	if (WIFEXITED(g_data.child_status))
		g_data.child_status = WEXITSTATUS(g_data.child_status);
}

void set_signals(int n)
{
	struct sigaction sa;

    sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	signal(SIGQUIT, SIG_IGN);
    sa.sa_flags = 0;
	if (n == 1)
	{
		sa.sa_handler = sigint_handler;
		if (sigaction(SIGINT, &sa, NULL) == -1)
        	perror("Error al configurar el manejador de señal");
	}
	if (n == 0)
	{
		sa.sa_handler = sigint_handler_child;
		if (sigaction(SIGINT, &sa, NULL) == -1)
        	perror("Error al configurar el manejador de señal");
	}
	
}

void leaks(void)
{
	system("leaks minishell");
}

//CHECKPOINT
int	main(int argc, char **argv ,char **env)
{	
	int n_lines;
	argc = 0;
	argv = NULL;
	ft_bzero(&g_data, sizeof(g_data));
	g_data.original_std_out = dup(STDOUT_FILENO);
	g_data.original_std_in = dup(STDIN_FILENO);
	n_lines = ft_arrlen(env);
	g_data.env = ft_calloc(sizeof(char *), (n_lines + 1));
	while (env[argc])
	{
		g_data.env[argc] = ft_strdup(env[argc]);
		argc++;
	}
	set_signals(1);
	atexit(leaks);
	init();
	return (0);
}
