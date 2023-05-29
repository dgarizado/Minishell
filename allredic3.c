/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allredic3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:54:37 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/29 17:53:56 by dgarizad         ###   ########.fr       */
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
		if (g_data.infiles[i][1] == '<' \
		&& g_data.infiles[i][2] == '<' && flag == 1)
		{
			ft_error_in(RED"minishell: syntax error near unexpected token `<'", \
			NULL, "'\n"RST_CLR, 258);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_open_outfile(int i)
{
	char	*aux; //leak?
	int		len;

	aux = ft_strtrim(g_data.redics[i], "> ");
	len = ft_arrlen(g_data.outfiles);
	if (g_data.redics[i][1] == '>' && g_data.redics[i][2] == '>')
	{
		printf(RED"minishell: syntax error near unexpected token `>'\n"RST_CLR);
		g_data.flags.here_doc_ret = 258;
		g_data.flags.here_doc_aux = i;
		return (258);
	}
	if (g_data.redics[i][1] == '>')
		g_data.fd_out = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		g_data.fd_out = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_data.fd_out != -1)
	{
		free(aux);
		if (strcmp(g_data.redics[i], g_data.outfiles[len - 1]) == 0) //FORBIDDEMN FUNCTION!
			dup2(g_data.fd_out, STDOUT_FILENO);
		//close(g_data.fd_out); //wtf?
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
int	ft_openn(int i)
{
	char	*aux; //Leak?
	int		len;

	aux = ft_strtrim(g_data.redics[i], "< ");
	if (g_data.infiles)
		len = ft_arrlen(g_data.infiles);
	g_data.fd_in = open(aux, O_RDONLY);
	if (g_data.fd_in != -1)
	{
		free(aux);
		if (strcmp(g_data.redics[i], g_data.infiles[len - 1]) == 0) //FORBIDDEN FUNCTION!
			dup2(g_data.fd_in, STDIN_FILENO);
		close(g_data.fd_in);
	}
	return (0);
}
