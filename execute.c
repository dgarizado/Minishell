/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:28:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/20 21:06:25 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static int	ft_execve(char **arr)
{
	char	*str_path;
	char	**matriz_command;
	
	gen_command_and_path(arr, g_data.env, &str_path, &matriz_command);
	execve(str_path, matriz_command, g_data.env);
	str_error(arr[0], "not found");
	return(127);
}

static int	ft_built_in(char **arr)
{
	if (!ft_strncmp(arr[0], "echo", ft_strlen(arr[0])))
		return(ft_echo(arr));
	else if (!ft_strncmp(arr[0], "export", ft_strlen(arr[0])))
		return(ft_export(arr));
	else if (!ft_strncmp(arr[0], "unset", ft_strlen(arr[0])))
		return(ft_unset(arr));
	else if (!ft_strncmp(arr[0], "cd", ft_strlen(arr[0])))
		return(ft_cd(arr));
	else if (!ft_strncmp(arr[0], "pwd", ft_strlen(arr[0])))
		return(ft_pwd(arr));
	else if (!ft_strncmp(arr[0], "env", ft_strlen(arr[0])))
		return(ft_env());
	else if (!ft_strncmp(arr[0], "exit", ft_strlen(arr[0])))
		return(ft_exit());
	else
		return (-1);
}

int	ft_execute(char **arr)
{
	int status;
	
	if (!arr || !(arr[0]))
		exit(str_error(arr[0], "missing arg"));
	status = ft_built_in(arr);
	if (status != -1)
	{
		//ft_abort(arr, ft_arrlen(arr));
		return (status);
	}
	else
	{
		status = ft_execve(arr);
		//ft_abort(arr, ft_arrlen(arr));
		return (status);
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