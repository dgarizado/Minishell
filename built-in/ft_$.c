/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_$.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:33:14 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/23 12:40:24 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


extern t_data	g_data;

int ft_$(void)
{
	printf("%d\n", g_data.child_status);
	return (EXIT_SUCCESS);
}