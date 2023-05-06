/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:45 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/05 19:17:04 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	
	if (*buffer)
	{
		printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	else
		return (errno);
}

int	ft_exit(void)
{
	exit (255);
	return (1);
}
