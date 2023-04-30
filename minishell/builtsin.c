/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:45 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/29 01:09:26 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[1024];

	printf("%s\n", getcwd(buffer, sizeof(buffer)));
	return (0);
}

int	ft_cd(char *newdir)
{
	chdir(newdir);
	return (0);
}

int	ft_exit(void)
{
	exit (0);
	return (0);
}
