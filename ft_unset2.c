/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:56:34 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/18 18:01:04 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

//return 0  if not encounter, return index when encounter
int	ft_get_var(char *str, int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (g_data.env[i][j] != '=')
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
