/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:28:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/18 22:31:42 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	ft_execve(char **arr)
{
	char	*str_path;
	char	**matriz_command;

	gen_command_and_path(arr, g_data.env, &str_path, &matriz_command);
	execve(str_path, matriz_command, g_data.env);
	str_error(arr[0], "not found");
	exit(127);
}

void	ft_built_in(char **arr)
{
	if (!ft_strncmp(arr[0], "echo", ft_strlen(arr[0])))
		exit(ft_echo(arr));
	else if (!ft_strncmp(arr[0], "pwd", ft_strlen(arr[0])))
		exit(ft_pwd(arr));
	else if (!ft_strncmp(arr[0], "env", ft_strlen(arr[0])))
		exit(ft_env());
	else if (!ft_strncmp(arr[0], "exit", ft_strlen(arr[0])))
		ft_exit();
}

void	ft_execute(char **arr)
{
	if (!arr || !(arr[0]))
		exit(str_error(arr[0], "missing arg"));
	ft_built_in(arr);
	ft_execve(arr);
}

/*
int main(int argc, char **argv, char **env)
{
	char *arr[3];
	arr[0] = "env";
	arr[1] = NULL;
	arr[2] = NULL;
	
	g_data.env = env;
	ft_execute(arr);
	return(0);
}*/