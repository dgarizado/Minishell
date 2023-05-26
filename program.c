/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:59:17 by dgarizad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/25 21:16:12 by vcereced         ###   ########.fr       */
=======
/*   Updated: 2023/05/26 16:38:54 by dgarizad         ###   ########.fr       */
>>>>>>> 73a117de331fed4ea76582dfe270215968810759
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
<<<<<<< HEAD
	write(1, "\n ----str BEFORE redic---", 25);
	printf("\n%s \n", str);
	ft_redic(str);
	write(1, "\n ----str after redic---", 25);
	printf("\n%s \n", str);
	write(1, "\n ----SPLIT NO \" \"---\n", 22);
=======

	// ft_redic(str);
	ft_redicc(str);
	//printf(YELLOW"\ninfiles: \n"RST_CLR);
	//ft_printf_arr(g_data.infiles);
>>>>>>> 73a117de331fed4ea76582dfe270215968810759
	g_data.flags.token1 = 1;
	tokenized_cmd = specialsplit(str, ' ');
	ft_printf_arr(tokenized_cmd);
	write(1, "\n----\n", 7);
	return (ft_execute(tokenized_cmd));
}
