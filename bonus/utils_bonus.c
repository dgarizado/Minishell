/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:41:15 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/11 20:27:15 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

int	ft_move_next_quotes(char *str, int i)
{
	char	flag;

	if (str[i] == '\'' || str[i] == '\"')
	{
		flag = str[i];
		i++;
		while (str[i] != flag && str[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}

void	ft_move_next_quotes_pip(char *str, int *n, int *j)
{
	char	flag;

	if (str[*j] == '\'' || str[*j] == '\"')
	{
		flag = str[*j];
		(*n)++;
		(*j)++;
		while (str[*j] != flag)
		{
			(*n)++;
			(*j)++;
		}
	}
}

static int	ft_move_next_priority_quote(char *arr, int i)
{
	int	n_parentesis;

	n_parentesis = 0;
	if (arr[i] == '(')
	{
		n_parentesis++;
		while (n_parentesis > 0 && arr[i] != '\0')
		{
			i++;
			if (arr[i] == '(')
				n_parentesis++;
			if (arr[i] == ')')
				n_parentesis--;
		}
	}
	return (i);
}

int	ft_check_to_or(char *arr)
{
	int		i;
	int		status;

	i = 0;
	while (arr[i])
	{
		i = ft_move_next_priority_quote(arr, i);
		if (!ft_strncmp(&arr[i], "||", 2))
		{
			status = ft_prompt_or(arr);
			return (status);
		}
		i++;
	}
	return (-1);
}

int	ft_check_to_and(char *arr)
{
	int	i;
	int	status;

	i = 0;
	while (arr[i])
	{
		i = ft_move_next_priority_quote(arr, i);
		if (!ft_strncmp(&(arr[i]), "&&", 2))
		{
			write(2, "TO -> OR\n", 10);
			status = ft_prompt_and(arr);
			return (status);
		}
		i++;
	}
	return (-1);
}
