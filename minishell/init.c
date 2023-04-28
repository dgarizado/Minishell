/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/28 22:47:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_data *data)
{
	data->redirector[INFILE] = "<";
	data->redirector[DELIMITER] = "<<";
	data->redirector[OUTFILE] = ">";
	data->redirector[APPEND] = ">>";
	data->separator[PIPE] = "|";
	data->separator[AND] = "&&";
	data->separator[OR] = "||";
	return (0);
}