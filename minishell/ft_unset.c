/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:56:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/06 02:54:34 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static int	ft_arrlen(char **env)
{
	int	n;

	n = 0;
	while (env[n])
		n++;
	return (n);
}

int ft_get_index_var(char *str)
{
	int i;

	i = 0;
	while (environ[i])
	{
		if(!ft_strncmp(*environ, str, ft_strlen(str)))
			return(i);
		i++;
	}
	return(0);
}

static char **ft_gen_new_env(char *str)
{
	char **new_env;
	int	len_env;
	int	i;
	int	n;
	char *swap;
	
	i = ft_get_index_var(str);
	swap = environ[i+1];
	free(environ[i]);
	environ[i] = swap;
	i++;
	while(environ[i])
	{
		swap = environ[i + 1];
		environ[i] =swap;
		i++;
	}
	
	return (new_env);
}

char **ft_export_unset(char **arr, char ***static_env)//NOT FINISH!!!!!!!!!!
{
	char **new_env;
	
	if (!environ)
	{
		str_error("unset", "env not found");
		return(NULL);
	}
	arr++;
	while(*arr)
	{
		if (getenv(*arr))
		{
			
			new_env = ft_gen_new_env(*arr);
			if (!(*static_env))
				*static_env = new_env;
			else
			{
				ft_abort(*static_env, ft_arrlen(*static_env));
				*static_env = new_env;
			}
		}
		else
			str_error("unset: not found;", *arr);
		arr++;
	}
	return (new_env);
}
