/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:45 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/06 15:53:27 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_pwd(char **arr)
{
	char	buffer[1024];
	
	memset(buffer, 0, sizeof(buffer));
	if ((arr[1]))
		return (str_error("pwd: bad option", arr[1]));
	printf("%s\n", getcwd(buffer, sizeof(buffer)));
	return (0);
}

int	ft_exit(void)
{
	// printf(YELLOW"\nG_data.env freeing: %p\n"RST_CLR" "RST_CLR, g_data.env);
	// ft_free_split(g_data.env);
	if (g_data.input)
		freelancer();
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_env(void)
{
	if (!g_data.env)
		return (str_error("env", "not available"));
	return (ft_printf_arr(g_data.env));
}
