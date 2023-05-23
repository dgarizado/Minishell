/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:45 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/23 12:04:08 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_pwd(char **arr)
{
	char	buffer[1024];
	if ((arr[1]))
		exit(str_error("pwd: bad option", arr[1]));
	printf("%s\n", getcwd(buffer, sizeof(buffer)));
	return (0);
}

int	ft_exit(void)
{
	exit (EXIT_SUCCESS);
	return (0);
}

int	ft_env(void)
{
	ft_printf_arr(g_data.env);
	return (0);
}
