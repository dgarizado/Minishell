/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:39:50 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/07 17:41:31 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static char	*ft_parse_str(char *str)
{
	if (ft_strchr(str, '=') && ft_strchr(str, '=')[1] == '=')
	{
		str_error_export("export", (ft_strchr(str, '=') + 2), " not found");
		return (NULL);
	}
	else if (ft_strchr(str, '=') && str[0] != '=')
		return (str);
	else
		return (NULL);
}

static void	ft_gen_new_env(char *str)
{
	char	**new_arr_env;

	if (!str)
		return ;
	new_arr_env = ft_gen_new_arr(ft_parse_str(str));
	if (new_arr_env)
	{
		ft_abort(g_data.env, ft_arrlen(g_data.env));
		g_data.env = new_arr_env;
	}
}

static void	ft_ch_value_var(char *arr, int n)
{
	if (ft_strchr(arr, '=') && arr[0] != '=')
	{
		if (ft_strchr(arr, '=')[1] != '=')
		{
			free(g_data.env[n]);
			g_data.env[n] = ft_strdup(arr);
		}
		else
			str_error_export("export", arr, " var found, wrong value");
	}
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
		while (g_data.env[n])
		{
			if (!ft_strncmp(g_data.env[n], arr[i], \
			(ft_str_index_chr(g_data.env[n], '='))))
			{
				flag = 0;
				ft_ch_value_var(arr[i], n);
			}
			n++;
		}
		if (flag == 1)
			ft_gen_new_env(arr[i]);
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
