/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:39:50 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/13 16:31:48 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

static void	ft_gen_new_env(char *str)
{
	char	**new_arr_env;

	if (!str)
		return ;
	new_arr_env = ft_gen_new_arr(str);
	if (new_arr_env)
	{
		ft_abort(g_data.env, ft_arrlen(g_data.env));
		g_data.env = new_arr_env;
	}
}

static void	ft_ch_value_var(char *arr, int n)
{
	free(g_data.env[n]);
	g_data.env[n] = ft_strdup(arr);
}

static int	ft_cmp_env_str(char *str, char *var_env, int flag, int n)
{
	if (!ft_strncmp(var_env, str, \
	(ft_str_index_chr(var_env, '='))))
	{
		flag = 0;
		ft_ch_value_var(str, n);
	}
	return (flag);
}

static void	ft_change_env(char **arr)
{
	int	i;
	int	n;
	int	flag;

	i = 1;
	while (arr[i])
	{
		flag = 1;
		n = 0;
		if (!ft_isdigit(arr[i][0]) && ft_isalpha(arr[i][0]))
		{
			while (g_data.env[n])
			{
				flag = ft_cmp_env_str(arr[i], g_data.env[n], flag, n);
				n++;
			}
			if (flag == 1)
				ft_gen_new_env(arr[i]);
		}
		else
			str_error_export("export", arr[i], "not a valid identifier");
		i++;
	}
}

int	ft_export(char **arr)
{
	int	n;

	if (!g_data.env)
		return (str_error("export", "env not found"));
	n = 0;
	if (!arr[1])
	{
		while (g_data.env[n])
		{
			write(1, "declare -x ", 12);
			printf("%s\n", g_data.env[n]);
			n++;
		}
	}
	else
		ft_change_env(arr);
	return (errno);
}
