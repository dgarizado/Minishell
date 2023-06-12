/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wedding_planner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/11 22:38:21 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

char	*ft_trim_priority_parentesis(char *str)
{
	char	*tmp;
	char	*str_trim_spce;
	char	*str_trim_parenthesis;

	//printf("trim_priority before %s\n", str);
	str_trim_spce = ft_strtrim(str, " ");
	//printf("trim_priority after spc %s\n", str);
	if (!ft_check_paralel_parenthesis(str_trim_spce))
	{
		//write(2, "ENTRA\n", 7);
		tmp = str_trim_spce;
		while (!ft_check_paralel_parenthesis(tmp))
		{
			str_trim_parenthesis = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
			free(tmp);
			tmp = str_trim_parenthesis;
			//printf("trim_priority after trim () %s\n", str);
		}
	}
	else
	{
		//printf("EXMAPLE A() %s\n", str_trim_spce);
		str_trim_parenthesis = ft_strdup(str_trim_spce);
		free(str_trim_spce);
	}
	//printf("RETURN() %s\n", str_trim_parenthesis);
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

	//printf("str in wedding planer %s\n", str);
	commands = special_split_pipe(str);
	//write(2, "\nWEDDING PLANNER\n", 18);
	//ft_printf_arr(commands);
	//if (!commands)
		//return (0);
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

	//write(2, "\nft_prompt_launcher\n", 21);
	//printf("\nbefore trim %s\n", arr);
	arr = ft_trim_priority_parentesis(arr);
	//printf("\nafter trim %s\n", arr);
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
