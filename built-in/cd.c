/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:06:28 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/13 17:33:18 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief Receives a string with the name of the
 * variable to update allways with the format "NAME=".
 * Assumes that the variable exists.
 * The function updates the value of the variable.
 * @param name 
 * @param value 
 * @return int 
 */
int	ft_change_env(char *name, char *value)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (g_data.env[n])
	{
		if (ft_strncmp(g_data.env[n], name, ft_strlen(name)) == 0)
		{
			free(g_data.env[n]);
			g_data.env[n] = ft_strjoin(name, value);
			return (0);
		}
		n++;
	}
	return (1);
}

/**
 * @brief Receives a string with
 * the name of the variable to update
 * allways with the format "NAME=".
 * The function updates the value of the
 * variable with the current working directory.
 * @return int 
 */
int	update_pwds(char *to_update)
{
	char	buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	getcwd(buffer, sizeof(buffer));
	ft_change_env(to_update, buffer);
	return (0);
}

static int	ch_home(char **arr)
{
	char	*path_home;
	int		status;

	path_home = getenv("HOME");
	status = chdir(path_home);
	if (status == 0)
	{
		update_pwds("PWD=");
		return (0);
	}
	else
		return (msg_error(arr[0], arr[1]));
}

int	ft_cd(char **arr)
{
	update_pwds("OLDPWD=");
	if (!arr || !*arr)
		return (127);
	else if (!arr[1])
		return (ch_home(arr));
	else if (chdir(arr[1]) == 0)
	{
		update_pwds("PWD=");
		return (0);
	}
	else
		return (msg_error(arr[0], arr[1]));
}
