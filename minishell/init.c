/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/29 00:07:16 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern t_data data;

int	operators(void)
{
	data.redirector[INFILE] = '<';
	//data.redirector[DELIMITER] = '<<';
	data.redirector[OUTFILE] = '>';
	//data.redirector[APPEND] = '>>';
	data.separator[PIPE] = '|';
	//data.separator[AND] = '&&';
	//data.separator[OR] = '||';
	return (0);
}

int	init(void)
{
	ft_memset(&data, '0', sizeof(data));
	printf("\n%lu\n", sizeof(data));
	operators();
	return (0);
}