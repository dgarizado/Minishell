/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:32:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/19 22:42:26 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern t_data	g_data;
t_data	g_data;

void	close_all_pipes(void)
{
	int	n;

	n = 0;
	while (n <= g_data.n_pipe)
	{
		close(g_data.pipes[n][STDIN_FILENO]);
		close(g_data.pipes[n][STDOUT_FILENO]);
		n++;
	}
	if (g_data.fd_infile)
		close(g_data.fd_infile);
	if (g_data.fd_outfile)
		close(g_data.fd_outfile);
}

void	receive_from_send_to_pipe(char *str)
{
	dup2(g_data.pipes[g_data.n_pipe - 1][STDIN_FILENO], STDIN_FILENO);
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	close_all_pipes();
	exit(ft_program(str));
}

void	sent_to_pipe(char *str)
{
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	close_all_pipes();
	exit(ft_program(str));
}

void	receive_from_pipe(char *str)
{
	dup2(g_data.pipes[g_data.n_pipe][STDIN_FILENO], STDIN_FILENO);
	close_all_pipes();
	exit(ft_program(str));
}