/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/23 20:13:56 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	set_env_to_global(char **env)
{
	g_data.env = env;
}

void	add_history_aux(char *input)
{
	char	*tmp;

	tmp = ft_strtrim(input, " ");
	if (ft_strlen(tmp) > 0)
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
	free(tmp);
}

/**
 * @brief Main process wont execute commands. 
 * it reads the input and then forks.
 * 
 * @return int 
 */
int	init(char **env)
{
	int	flag;

	ft_bzero(&g_data, sizeof(g_data));
	set_env_to_global(env);
	while (1)
	{
		g_data.input = readline(PINK"mi"YELLOW"ni"BLUE"hell🐢"RST_CLR"$>");
		if (g_data.input[0] != '\0')
		{
			add_history_aux(g_data.input);
			flag = ft_lexic((g_data.input));
			if (flag == -1)
			{
				g_data.child_pid = fork();
				if (g_data.child_pid == 0)
					init_prompt();
			}
			g_data.child_status = flag;
			waitpid(g_data.child_pid, &g_data.child_status, WUNTRACED);
			if (WIFEXITED(g_data.child_status))
				g_data.child_status = WEXITSTATUS(g_data.child_status);
			printf("\n:%d\n", g_data.child_status);
			free((g_data.input));
		}
	}
	return (EXIT_SUCCESS);
}
