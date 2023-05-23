/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:39:50 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/23 20:06:59 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static char	**ft_gen_new_arr(char **arr_parsed)
{
	char	**new_env;
	int		len_env;
	int		i;
	int		n;

	i = 0;
	n = 0;
	len_env = ft_arrlen(g_data.env);
	new_env = (char **)malloc(sizeof(char *) * (len_env + 1 + \
	ft_arrlen(arr_parsed)));
	while (i < len_env)
	{
		new_env[i] = ft_strdup(g_data.env[i]);
		i++;
	}
	while (i < len_env + ft_arrlen(arr_parsed))
		new_env[i++] = ft_strdup(arr_parsed[n++]);
	new_env[i] = NULL;
	return (new_env);
}

static int	ft_parse_count(char **arr)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '=') && arr[i][0] != '=')
			count++;
		i++;
	}
	return (count);
}

static char	**ft_parse_arr(char **arr)
{
	char	**arr_parsed;
	int		n;
	int		i;
	char	*ptr;

	i = 0;
	arr_parsed = (char **)malloc(sizeof (char *) * (ft_parse_count(arr) + 1));
	n = 0;
	while (i < ft_arrlen(arr))
	{
		if (ft_strchr(arr[i], '='))
		{
			ptr = ft_strchr(arr[i], '=');
			if (ptr[1] == '=')
				str_error_export("minishell", (ft_strchr(arr[i], '=') + 2), " not found");
			else if (ft_strchr(arr[i], '=') && arr[i][0] != '=')
			{
				arr_parsed[n] = ft_strdup(arr[i]);
				n++;
			}
		}
		i++;
	}
	arr_parsed[n] = NULL;
	return (arr_parsed);
}

static char	**ft_gen_new_env(char **arr)
{
	char	**arr_parsed;
	char	**new_arr_env;

	arr_parsed = ft_parse_arr(arr);
	new_arr_env = ft_gen_new_arr(arr_parsed);
	if (g_data.flag_env != 0)
		ft_abort(g_data.env, ft_arrlen(g_data.env));
	ft_abort(arr_parsed, ft_arrlen(arr_parsed));
	g_data.flag_env++;
	return (new_arr_env);
}

int	ft_export(char **arr)
{
	if (!g_data.env)
		return (str_error("export", "env not found"));
	if (!arr[1])
		return (ft_printf_arr(g_data.env));
	else
		g_data.env = ft_gen_new_env(arr);
	return (errno);
}
