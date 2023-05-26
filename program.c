/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:59:17 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/27 00:43:13 by vcereced         ###   ########.fr       */
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
	char	**tokenized_cmd; //NEED FREE?

	//ft_redic(str);
	ft_redicc(str);
	//printf(YELLOW"\ninfiles: \n"RST_CLR);
	//ft_printf_arr(g_data.infiles);
	g_data.flags.token1 = 1;
	tokenized_cmd = specialsplit(str, ' ');
	//ft_printf_arr(tokenized_cmd);
	//write(1, "\n----\n", 7);
	return (ft_execute(tokenized_cmd));
}
