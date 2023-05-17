/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:56:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/17 21:16:35 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data; g_data;

int ft_get_var(char *str)//return 0  if not encounter, return index when encounter
{
	int i;

	i = 0;
	while (g_data.env[i])
	{
		if(!ft_strncmp(g_data.env[i], str, ft_strlen(str)))
			return(i);
		i++;
	}
	return(0);
}

static int ft_count_to_clear(char **arr)
{
	int nvar_to_clear;
	int i;
	int n;
	
	nvar_to_clear = 0;
	while(g_data.env[i])
	{
		n = 0;
		while(arr[n])
		{
			if (ft_get_var(arr[n]) != 0)
				nvar_to_clear++;
			n++;
		}
		i++;
	}
	return (nvar_to_clear);
}

static char	**ft_gen_new_arr(char **arr)
{
	char **new_arr_env;
	int	len_new_env;
	int i;
	int n;
	
	len_new_env = ft_arrlen(g_data.env) - ft_count_to_clear(arr);
	new_arr_env = (char **)malloc(sizeof(char *) * len_new_env + 1);
	i = 0;
	n= 0;
	while (i < len_new_env)
	{
		if (ft_get_var(arr[n]) != 0)
		{
			new_arr_env[n] = ft_strdup(arr[i]);
			n++;
		}
		i++;
	}
	new_arr_env[n] = NULL;
	return (new_arr_env);
}

static char **ft_gen_new_env(char *arr)
{
	char	**new_arr_env;

	new_arr_env = ft_gen_new_arr(arr);
	if (g_data.flag_env != 0)
		ft_abort(g_data.env, ft_arrlen(g_data.env));
	g_data.flag_env++;
	return (new_arr_env);
}

char **ft_unset(char **arr, char ***static_env)
{
	char **new_env;
	
	if (!g_data.env)
	{
		str_error("unset", "env not found");
		return(EXIT_FAILURE);
	}
	if (!arr[1])
	{
		str_error("unset", "enough arguments");
		return (EXIT_SUCCESS);
	}
	g_data.env = ft_gen_new_env(arr);
	return (errno);
}
