/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:35:22 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/09 20:38:39 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

int	ft_alexic(void)
{
	int	i;

	i = 0;
	if (g_data.input_ex[0] == '|' && g_data.input_ex[1] == '|')
	{
		str_error("minishell", "syntax error near unexpected token `||'");
		return (258);
	}
	while (g_data.input[i] != '\0')
	{
		if (g_data.input[i] == '|' && g_data.input[i + 1] == '|' \
		&& g_data.input[i + 2] == '|')
		{
			str_error("minishell", "syntax error near unexpected token `|'");
			return (258);
		}
		i++;
	}
	return (0);
}
