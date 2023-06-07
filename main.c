/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/07 17:46:32 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	sigint_handler_child(int sig)
{
	sig = 0;
	exit(127);
}

void	sigint_handler(int sig)
{
	sig = 0;
	if (g_data.flags.father == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n\033[F\033[K"PINK"mi"YELLOW"ni"BLUE"hell🐢"RST_CLR"$>\n");
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

void	set_signals(int n)
{
	struct sigaction	sa;

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

/**
 * @brief Set the env to global object
 */
static void	set_env_to_global(char **env)
{
	int	n_lines;
	int	i;

	n_lines = ft_arrlen(env);
	g_data.env = ft_calloc(sizeof(char *), (n_lines + 1));
	i = 0;
	while (env[i])
	{
		g_data.env[i] = ft_strdup(env[i]);
		i++;
	}
}

//atexit(leaks);
int	main(int argc, char **argv, char **env)
{	
	argc = 0;
	argv = NULL;
	ft_bzero(&g_data, sizeof(g_data));
	g_data.original_std_out = dup(STDOUT_FILENO);
	g_data.original_std_in = dup(STDIN_FILENO);
	set_env_to_global(env);
	set_signals(1);
	init();
	return (0);
}
