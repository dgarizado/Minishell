/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:23:03 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/07 16:29:22 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	gen_new_pipe(char **arr)
{
	int i;
	int n;

	n = (ft_arrlen(arr) - 1);
	g_data.pipes = (int **)malloc(sizeof(int *) * n);
	if (!g_data.pipes)
		exit(msg_error("pipex", "allocation memory gen pipes"));

	i = 0;
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

static void	fork_proccess(int *pids)
{
	static int i = 0;
	
	g_data.pid = fork();
	pids[i] = g_data.pid;
	if (g_data.pid == -1)
		exit(msg_error("pipex", "error forking"));
	i++;
}

static void ft_wait(void)
{	
	int i = 0;
	
	if (g_data.flags.concurrency == 1)
		waitpid(g_data.pid, &g_data.child_status, 0);
	else
		i = waitpid(g_data.pid, &g_data.child_status, WNOHANG);
	if (WIFEXITED(g_data.child_status))
	{
		g_data.child_status = WEXITSTATUS(g_data.child_status);
		if (g_data.child_status == 127)
			exit(127);
	}
}

static void	pipe_and_fork(char **arr, int *pids)
{
	g_data.n_pipe = 0;
	gen_new_pipe(arr);
	 fork_proccess(pids);
	if (g_data.pid == 0)
		sent_to_pipe(arr[g_data.n_pipe]);
	while (g_data.n_pipe < (ft_arrlen(arr) - 2))
	{
		close(g_data.pipes[g_data.n_pipe][STDOUT_FILENO]);
		g_data.n_pipe++;
		ft_wait();
		fork_proccess(pids);
		if (g_data.pid == 0)
			receive_from_send_to_pipe(arr[g_data.n_pipe]);
	}
	close(g_data.pipes[g_data.n_pipe][STDOUT_FILENO]);
	ft_wait();
	fork_proccess(pids);
	if (g_data.pid == 0)
		receive_from_pipe(arr[g_data.n_pipe + 1]);
}

int ft_pipex(char **arr)
{
	int wstatus;
	int statuscode;
	int pids[100];
	int i = 0;
	
	memset(pids, 0, sizeof(pids));
	pipe_and_fork(arr, pids);
	waitpid(g_data.pid, &wstatus, 0);
	while (pids[i] != 0)
	{
		kill(pids[i], 9);
		i++;
	}
	if (WIFEXITED(wstatus))
	{
		statuscode = WEXITSTATUS(wstatus);
		if (statuscode != 0)
			exit(statuscode);
	}
	exit(EXIT_SUCCESS);
}
