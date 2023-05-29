/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:28:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/27 00:42:32 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static int	ft_execve(char **arr)
{
	char	*str_path;
	char	**matriz_command;
	
	gen_command_and_path(arr, g_data.env, &str_path, &matriz_command);
	//write(1, "----\n", 6);
	//ft_printf_arr(matriz_command);
	//printf("\n path -> %s\n", str_path);
	execve(str_path, matriz_command, g_data.env);
	return (str_error(arr[0], "command not found"));
	//return(127);
}

static int	ft_built_in(char **arr)
{
	if (!ft_strncmp(arr[0], "echo", 4))
		return(ft_echo(arr));
	else if (!ft_strncmp(arr[0], "export", 6))
		return(ft_export(arr));
	else if (!ft_strncmp(arr[0], "unset", 5))
		return(ft_unset(arr));
	else if (!ft_strncmp(arr[0], "cd", 2))
		return(ft_cd(arr));
	else if (!ft_strncmp(arr[0], "pwd", 3))
		return(ft_pwd(arr));
	else if (!ft_strncmp(arr[0], "env", 3))
		return(ft_env());
	else if (!ft_strncmp(arr[0], "exit", 4))
		return(ft_exit());
	else if (!ft_strncmp(arr[0], "$?", 4))
	return(ft_$());
	else
		return (-1);
}

int	ft_execute(char **arr)
{
	int status;
	
	if (!arr || !(arr[0]))
		return (str_error(arr[0], "missing arg"));
	status = ft_built_in(arr);
	if (status != -1)
	{
		//ft_abort(arr, ft_arrlen(arr));
		return (status);
	}
	else
	{
		//ft_abort(arr, ft_arrlen(arr));
		return (ft_execve(arr));
	}
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