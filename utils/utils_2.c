/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:35:22 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/10 19:23:07 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

static void	ft_msg_lexic(int n_parenthesis)
{
	if (n_parenthesis > 0)
		str_error("minishell", "syntax error unclosed token `('");
	else if (n_parenthesis < 0)
		str_error("minishell", "syntax error unclosed token `)'");
}

static int	ft_unclosed_parenthesis(void)
{
	int	i;
	int	n_parenthesis;

	i = 0;
	n_parenthesis = 0;
	while (g_data.input_ex[i])
	{
		if (g_data.input_ex[i] == '(' || g_data.input_ex[i] == ')')
		{
			if (g_data.input_ex[i] == '(')
				n_parenthesis++;
			else
				n_parenthesis--;
			i++;
		}
		else
		{
			i = ft_move_next_quotes(g_data.input_ex, i);
			i++;
		}
	}
	ft_msg_lexic(n_parenthesis);
	return (n_parenthesis);
}

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
	if (ft_unclosed_parenthesis() != 0)
		return (258);
	return (0);
}
