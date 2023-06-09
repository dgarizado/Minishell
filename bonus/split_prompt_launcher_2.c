/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt_launcher_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:32:28 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/09 18:46:05 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

int	ft_move_next_parenthesis(char *str, int i)
{
	if (str[i] == '(')
	{
		i++;
		while (str[i] != ')')
			i++;
	}
	return (i);
}
