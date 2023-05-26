/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:23:03 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/26 23:11:22 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;
//t_data	g_data;

void	gen_pipes(char **arr)
{
	int i;
	int n;

	i = 0;
	n = (ft_arrlen(arr) - 1);
	g_data.pipes = (int **)malloc(sizeof(int) * n);
	if (!g_data.pipes)
		exit(msg_error("pipex", "allocation memory gen pipes"));
	while (i < n)
	{
		g_data.pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!g_data.pipes[i])
			exit(msg_error("pipex", "allocation memory gen pipes"));
		if (pipe(g_data.pipes[i]) == -1)
			exit(msg_error("pipex", "error gen pipes"));
		i++;
	}
}

static void	fork_proccess(void)
{
	g_data.pid = fork();
	if (g_data.pid == -1)
		exit(msg_error("pipex", "error forking"));
}

static void pipe_and_fork(char **arr)
{
	g_data.n_pipe = 0;
	gen_pipes(arr);
	fork_proccess();
	if (g_data.pid == 0)
		sent_to_pipe(arr[g_data.n_pipe]);
	while (g_data.n_pipe < (ft_arrlen(arr) - 2))
	{
		g_data.n_pipe++;
		wait(NULL);
		fork_proccess();
		if (g_data.pid == 0)
			receive_from_send_to_pipe(arr[g_data.n_pipe]);
	}
	wait(NULL);
	fork_proccess();
	if (g_data.pid == 0)
	{
		receive_from_pipe(arr[g_data.n_pipe + 1]);
	}
	close_all_pipes();
}

int ft_pipex(char **arr)
{
	int wstatus;
	int statuscode;

//	if (!arr ||  !arr[0])
//		str_error("pipex", "no argument");
	pipe_and_fork(arr);
	waitpid(g_data.pid, &wstatus, WUNTRACED);
	if (WIFEXITED(wstatus))
	{
		statuscode = WEXITSTATUS(wstatus);
		if (statuscode != 0)
			exit(statuscode);
	}
	//free_pipex(pipex);
	exit(EXIT_SUCCESS);//no deberia salir con este exit sino con el de el ultimo hihjo
}
