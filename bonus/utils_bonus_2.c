/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:51:45 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/11 18:34:44 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

int	status_and_free(char **prompts, int status)
{
	ft_free_split(prompts);
	return (status);
}

int	ft_to_program(char **commands)
{
	pid_t	pid;
	int		status;
	int		wstatus;
	int		statuscode;

	statuscode = 0;
	pid = fork();
	if (pid == 0)
	{
		status = ft_program(commands[0]);
		ft_free_split(commands);
		freelancer();
		exit(status);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		statuscode = WEXITSTATUS(wstatus);
	return (statuscode);
}

/**
 * @brief check if starts with '(' and finish with ')', 
 * then checks if there are paralel '( )'
 * @param str_trimed 
 * @return int 1 if not paralel '( )', return 0 if yes
 */
int	ft_check_paralel_parenthesis(char *str_trimed)
{
	int	i;
	int	n_parentesis;

	i = 0;
	n_parentesis = 0;
	if (str_trimed[0] == '(' && str_trimed[ft_strlen(str_trimed) - 1] == ')')
	{
		while (str_trimed[i] != '\0')
		{
			if (str_trimed[i] == '(')
				n_parentesis++;
			if (str_trimed[i] == ')')
				n_parentesis--;
			if (n_parentesis == 0)
				break ;
			i++;
		}
	}
	if (i == ((int)ft_strlen(str_trimed) - 1))
		return (1);
	else
		return (0);
}
