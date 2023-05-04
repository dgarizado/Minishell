/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:59:17 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/04 23:40:38 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_redic(char *str)
{
	int		i;
	char	*redirector;
	
	i = 0;
	while (i < REDIR_COUNT)
	{
		redirector = ft_strchr(str, g_data.redirector[i]);
		if (redirector != NULL)
			printf("\nFOUND:'%s'\n", redirector);
		i++;
	}
	return (0);
}
int	ft_program(char *str)
{
	ft_redic(str);
	return (0);
}