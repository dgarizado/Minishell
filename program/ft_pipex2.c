/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:32:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/12 17:28:28 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

void	receive_from_send_to_pipe(char *str)
{
	int	status;

	dup2(g_data.pipes[g_data.n_pipe - 1][STDIN_FILENO], STDIN_FILENO);
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	status = ft_prompt_launcher(str);
	freelancer();
	ft_free_split(g_data.env);
	exit(status);
}

void	sent_to_pipe(char *str)
{
	int	status;

	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	status = ft_prompt_launcher(str);
	freelancer();
	ft_free_split(g_data.env);
	exit(status);
}

void	receive_from_pipe(char *str)
{
	int	status;

	dup2(g_data.pipes[g_data.n_pipe][STDIN_FILENO], STDIN_FILENO);
	status = ft_prompt_launcher(str);
	freelancer();
	ft_free_split(g_data.env);
	exit(status);
}
