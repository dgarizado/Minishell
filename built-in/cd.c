/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:06:28 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/04 20:26:37 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief Receives a string with the name of the
 * variable to update allways with the format "NAME=".
 * Assumes that the variable exists.
 * The function updates the value of the variable.
 * @param name 
 * @param value 
 * @return int 
 */
int ft_change_env(char *name, char *value)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (g_data.env[n])
	{
		if (ft_strncmp(g_data.env[n], name, ft_strlen(name)) == 0)
		{
			g_data.env[n] = ft_strjoin(name, value); //LEAK??
			return (0);
		}
		n++;
	}
	return (1);
}

/**
 * @brief Receives a string with
 * the name of the variable to update
 * allways with the format "NAME=".
 * The function updates the value of the
 * variable with the current working directory.
 * @return int 
 */
int update_pwds(char *to_update)
{
	//char	*oldpwd;
	char	buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	getcwd(buffer, sizeof(buffer));
	ft_change_env(to_update, buffer);
	return (0);
}

static int	ch_home(char **arr)
{
	char	*path_home;
	int		status;

	// path_home = gen_path_home();
	path_home = getenv("HOME");
	status = chdir(path_home);
	// if (path_home)
	// 	free(path_home);
	if (status == 0)
	{
		update_pwds("PWD=");
		return (0);
	}
	else
		return (msg_error(arr[0], arr[1]));
}

static int	count_args(char **arr)
{
	int	n;

	n = 0;
	while (arr[n])
		n++;
	return (n);
}

int	ft_cd(char **arr)
{
	update_pwds("OLDPWD=");
	if (!arr || !*arr)
		return (127);
	else if (count_args(arr) > 3)
		return (str_error(arr[0], "too many arguments"));
	else if (count_args(arr) == 3)
		return (chdir_swap(swap_arg(arr[1], arr[2]), arr));
	else if (!arr[1])
		return (ch_home(arr));
	else if (chdir(arr[1]) == 0)
	{
		update_pwds("PWD=");
		return (0);
	}
	else
		return (msg_error(arr[0], arr[1]));
}
/*
void	swap_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc -1)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[argc - 1] = NULL;
}

int	main(int argc, char **argv)
{
	char	vector[256];
	int		status;
	swap_argv(argc, argv);
	printf("\n****DIRECCION before  %s\n", getcwd(vector, sizeof(vector)));
	status = ft_cd(argv);
	printf("DIRECCION afteeerr  %s\n", getcwd(vector, sizeof(vector)));
	printf("****salida STATUS %d\n\n", status);
	//atexit(check);
	return (0);
}
*/