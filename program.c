/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:59:17 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/04 20:20:20 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Reveives a unique string containing only one command and
 * their redirections. 
 * Checks if there are redirections and removes them from
 * the arguments.
 * Stores the redirection names in two arrays (for infiles and for outifiles)
 * @param str 
 * @return int 
 */
int	ft_program(char *str)
{
	char	**tokenized_cmd; //NEED FREE? ABSOLUTELY YES
	//ft_redic(str);
	//printf(YELLOW"\ninfiles: \n"RST_CLR);
	//ft_printf_arr(g_data.infiles);
	ft_redicc(str);
	g_data.flags.token1 = 1;
	// printf(RED"\nENTERED FROM HERE: str:%s : %p\n"RST_CLR"."RST_CLR, str, str);
	//free(str);
	tokenized_cmd = specialsplit(str, ' ');
	// printf(PINK"\nTOKENIZED COMMAND: %p : %s\n"RST_CLR"\n"RST_CLR, (tokenized_cmd), (tokenized_cmd[0]));
	//write(1, "\n----\n", 7);
	// ft_printf_arr(tokenized_cmd);
	//ft_abort(g_data.commands, ft_arrlen(g_data.commands));//VICTOR
	return (ft_execute(tokenized_cmd));
}
