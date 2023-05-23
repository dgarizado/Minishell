/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:54:37 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/23 20:58:09 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	check_here_docs(void)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (g_data.infiles[i])
	{
		if (g_data.infiles[i][1] == '<' && g_data.infiles[i][2] != '<')
			flag = 1;
		if (g_data.infiles[i][1] == '<' && g_data.infiles[i][2] == '<' && flag == 1)
		{
			ft_error_in(RED"minishell: syntax error near unexpected token `<'",\
			 NULL, "'\n"RST_CLR, 258);
			break ;
		}
		i++;
	}
	return (0);
}
/**
 * @brief Here we open the infiles
 * that are not here_doc. It doest not matter
 * if the open fails, because the error will be
 * handled in the check_infiles function. 
 * @param i 
 * @return int 
 */
int	ft_open(int i)
{
	char	*aux;

	aux = ft_strtrim(g_data.infiles[i], "< ");
	g_data.fd_in = open(aux, O_RDONLY);
	if (g_data.fd_in != -1)
	{
		free(aux);
		if (g_data.infiles[i + 1] == NULL)
			dup2(g_data.fd_in, STDIN_FILENO);
		close(g_data.fd_in);
	}
	return (0);
}
