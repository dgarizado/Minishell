/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/08 22:57:30 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

char *ft_trim_priority_parentesis(char *str)
{
	char *tmp;
	char *str_trim_spce;
	char *str_trim_parenthesis;
	
	str_trim_spce = ft_strtrim(str, " ");
	if (str_trim_spce[0] == '(' && str_trim_spce[ft_strlen(str_trim_spce) - 1] == ')')
	{
		tmp = str_trim_spce;
		while(tmp[0] == '(' && tmp[ft_strlen(tmp) - 1] == ')')
		{
			str_trim_parenthesis = ft_substr(tmp, 1, ft_strlen(tmp) -2);
			free(tmp);
			tmp = str_trim_parenthesis;
		}
	}
	else
	{
		str_trim_parenthesis = ft_strdup(str_trim_spce);	
		free(str_trim_spce);
	}
	return (str_trim_parenthesis);
}

int ft_prompt_AND(char *arr)
{
	char	**misiles;
	int		status;
	int		i;
	
	misiles = special_split_launcher(arr, "&&");
	i = 0;
	if (ft_arrlen(misiles) > 1)
	{
		while (misiles[i])
		{
			status = ft_prompt_launcher(misiles[i]);
			if (status != EXIT_SUCCESS)
			{
				return(status_and_free(misiles, status));
				//ft_free_split(misiles);
				//return(status);
			}
			i++;
		}
		return(status_and_free(misiles, status));
		//ft_free_split(misiles);
		//return(status);
	}
	else
	{
		status = ft_prompt_AND(misiles[0]);
		return(status_and_free(misiles, status));
		//ft_free_split(misiles);
		//return(status);
	}
}

int ft_prompt_OR(char *arr)
{
	char	**misiles;
	int	status;
	int	i;
	
	misiles = special_split_launcher(arr, "||");
	i = 0;
	if (ft_arrlen(misiles) > 1)
	{
		while (misiles[i])
		{
			status = ft_prompt_launcher(misiles[i]);
			if (status == EXIT_SUCCESS)
			{
				return(status_and_free(misiles, status));
				//ft_free_split(misiles);
				//return(status);
			}
			i++;
		}
		return(status_and_free(misiles, status));
		//ft_free_split(misiles);
		//return(status);
	}
	else
	{
		status = ft_prompt_OR(misiles[0]);
		return(status_and_free(misiles, status));
		//ft_free_split(misiles);
		//return(status);
	}
}


int ft_prompt_launcher(char *arr)
{
	int status;
	arr = ft_trim_priority_parentesis(arr);
	status = ft_check_to_AND(arr);
	if (status != -1)
		return (status);
	status = ft_check_to_OR(arr);
	if (status != -1)
		return (status);
	status = ft_program(arr);
	free(arr);
	return (status);
}

/**
 * @brief Counts pipes and allocates 
 * pipes + 2 strings (for NULL terminating and for the last command)
 * 
 * @return int 
 */

int	wedding_planner(void)
{
	g_data.flags.token1 = 0;
	g_data.commands = special_split_pipe(g_data.input_ex);
	free(g_data.input_ex);
	if (ft_arrlen(g_data.commands) > 1)
	{
		exit(ft_pipex(g_data.commands));
	}
	else
	{
		exit(ft_prompt_launcher(g_data.commands[0]));
	}
	return (0);
}
