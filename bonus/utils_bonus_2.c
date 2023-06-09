/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:51:45 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/09 18:39:07 by vcereced         ###   ########.fr       */
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
