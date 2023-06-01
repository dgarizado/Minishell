/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:29 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/01 20:54:43 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Checks if there is any infile or outfile with 
 * more than two '<' characters.
 * 
 * @param i 
 * @return int 
 */
int	aux_dell(int i)
{
	while (g_data.redics[i])
	{
		ignore_redics(g_data.redics[i], &i);
		if (g_data.redics[i][1] == '<' && g_data.redics[i][2] == '<')
		{
			printf(RED"minishell: syntax error near unexpected token `<'\n"RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		if (g_data.redics[i][1] == '>' && g_data.redics[i][2] == '>')
		{
			printf(RED"minishell: syntax error near unexpected token `>'\n"RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		i++;
	}
	return (i);
}
