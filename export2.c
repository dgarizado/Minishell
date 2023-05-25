/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:39:50 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/25 00:58:18 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static char	**ft_gen_new_arr(char *str_parsed)
{
	char	**new_env;
	int		len_env;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (str_parsed == NULL)
		return (NULL);
	len_env = ft_arrlen(g_data.env);
	new_env = (char **)malloc(sizeof(char *) * (len_env + 2));
	while (i < len_env)
	{
		new_env[i] = ft_strdup(g_data.env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(str_parsed);
	new_env[i] = NULL;
	return (new_env);
}

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
		if (g_data.flag_env != 0)
			ft_abort(g_data.env, ft_arrlen(g_data.env));
		g_data.flag_env++;
		g_data.env = new_arr_env;
	}
}

static void	ft_ch_value_var(char *arr, int n)
{
	if (ft_strchr(arr, '=') && arr[0] != '=')
	{
		if (ft_strchr(arr, '=')[1] != '=')
			g_data.env[n] = ft_strdup(arr);
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
			if (!ft_strncmp(g_data.env[n], arr[i], (ft_str_index_chr(g_data.env[n], '='))))
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
