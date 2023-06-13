/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:56:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/12 23:25:53 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

static int	ft_count_to_clear(char **arr)
{
	int	nvar_to_clear;
	int	i;
	int	n;

	i = 0;
	nvar_to_clear = 0;
	while (g_data.env[i])
	{
		n = 0;
		while (arr[n])
		{
			if (ft_get_var(arr[n], i) == 1)
				nvar_to_clear++;
			n++;
		}
		i++;
	}
	return (nvar_to_clear);
}

static char	**ft_gen_new_arr_unset(char **arr)
{
	char	**new_arr_env;
	int		len_new_env;
	int		i;
	int		n;

	len_new_env = 0;
	i = 0;
	n = 0;
	if (!ft_count_to_clear(arr))
		return (NULL);
	len_new_env = ft_arrlen(g_data.env) - ft_count_to_clear(arr);
	new_arr_env = (char **)ft_calloc(sizeof(char *), len_new_env + 1);
	while (i < ft_arrlen(g_data.env))
	{
		ft_copy(new_arr_env, arr, i, &n);
		i++;
	}
	return (new_arr_env);
}

static void	ft_gen_new_env2(char **arr)
{
	char	**new_arr_env;

	new_arr_env = ft_gen_new_arr_unset(arr);
	if (new_arr_env)
	{
		ft_abort(g_data.env, ft_arrlen(g_data.env));
		g_data.env = new_arr_env;
	}
}

int	ft_unset(char **arr)
{	
	if (!g_data.env)
	{
		str_error("unset", "env not found");
		return (EXIT_FAILURE);
	}
	else if (!arr[1])
	{
		str_error("unset", "not enough arguments");
		return (EXIT_SUCCESS);
	}
	else
		ft_gen_new_env2(arr);
	return (errno);
}
