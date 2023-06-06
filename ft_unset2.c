/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:56:34 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/06 17:42:56 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_get_var(char *str, int n)
{
	int	j;

	j = 0;
	while (g_data.env[n][j] != '=')
		j++;
	if (!ft_strncmp(g_data.env[n], str, j))
		return (1);
	return (0);
}

void	ft_copy(char **new_arr_env, char **arr, int i, int *n)
{
	int	encounter;
	int	j;

	j = 0;
	encounter = 0;
	while (arr[j])
	{
		if (ft_get_var(arr[j], i) != 0)
			encounter++;
		j++;
	}
	if (encounter == 0)
	{
		new_arr_env[*n] = ft_strdup(g_data.env[i]);
		(*n)++;
	}
}
