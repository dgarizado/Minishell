/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/11 18:33:22 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

char	*ft_trim_priority_parentesis(char *str)
{
	char	*tmp;
	char	*str_trim_spce;
	char	*str_trim_parenthesis;

	str_trim_spce = ft_strtrim(str, " ");
	if (ft_check_paralel_parenthesis(str_trim_spce) == 1)
	{
		tmp = str_trim_spce;
		while (ft_check_paralel_parenthesis(tmp) == 1)
		{
			str_trim_parenthesis = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
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

int	ft_prompt_and(char *arr)
{
	char	**prompts;
	int		status;
	int		i;

	prompts = special_split_launcher(arr, "&&");
	i = 0;
	if (ft_arrlen(prompts) > 1)
	{
		while (prompts[i])
		{
			status = ft_prompt_launcher(prompts[i]);
			if (status != EXIT_SUCCESS)
			{
				return (status_and_free(prompts, status));
			}
			i++;
		}
		return (status_and_free(prompts, status));
	}
	else
	{
		status = wedding_planner(prompts[0]);
		return (status_and_free(prompts, status));
	}
}

int	ft_prompt_or(char *arr)
{
	char	**prompts;
	int		status;
	int		i;

	prompts = special_split_launcher(arr, "||");
	i = 0;
	if (ft_arrlen(prompts) > 1)
	{
		while (prompts[i])
		{
			status = ft_prompt_launcher(prompts[i]);
			if (status == EXIT_SUCCESS)
			{
				return (status_and_free(prompts, status));
			}
			i++;
		}
		return (status_and_free(prompts, status));
	}
	else
	{
		status = wedding_planner(prompts[0]);
		return (status_and_free(prompts, status));
	}
}

/*
 * @brief split the string received and discover if it has 1 or more 
 * prompts to execute. So send the prompts to pipex or just execute the 
 * lonely prompt.

 * @return int return status of the prompt or the last prompt of pipex
 */

int	wedding_planner(char *str)
{
	int		status;
	char	**commands;

	commands = special_split_pipe(str);
	if (ft_arrlen(commands) > 1)
	{
		status = ft_pipex(commands);
		ft_free_split(commands);
		return (status);
	}
	else
	{
		status = ft_to_program(commands);
		ft_free_split(commands);
		return (status);
	}
	return (0);
}

int	ft_prompt_launcher(char *arr)
{
	int	status;

	arr = ft_trim_priority_parentesis(arr);
	status = ft_check_to_and(arr);
	if (status != -1)
	{
		free(arr);
		return (status);
	}
	status = ft_check_to_or(arr);
	if (status != -1)
	{
		free(arr);
		return (status);
	}
	status = wedding_planner(arr);
	free(arr);
	return (status);
}
