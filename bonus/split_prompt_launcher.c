/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt_launcher.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:11:07 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/11 19:36:52 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

static int	count_str2(char *str, char *c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = ft_move_next_quotes(str, i);
		i = ft_move_next_parenthesis(str, i);
		if (ft_strncmp(&(str[i]), c, ft_strlen(c)) \
		&& !ft_strncmp(&(str[i + 1]), c, ft_strlen(c)))
		{
			count++;
			i = i + ft_strlen(c);
		}
		else if (ft_strncmp(&(str[i]), c, 2) && str[i + 1] == '\0')
		{
			count++;
			break ;
		}
		i++;
	}
	return (count);
}

static	void	ft_aux(char *str, int *n, int *j)
{
	int		n_parentesis;

	n_parentesis = 0;
	if (str[*j] == '(')
	{
		n_parentesis++;
		(*j)++;
		(*n)++;
		while ((str[*j] != ')' || n_parentesis > 0) && str[*j] != '\0')
		{
			(*j)++;
			(*n)++;
			if (str[*j] == '(')
				n_parentesis++;
			if (str[*j] == ')')
				n_parentesis--;
		}
	}
}

static char	*gen_string_with2(char *str, int *j, char *c)
{
	int		n;

	n = 0;
	while (ft_strncmp(&(str[*j]), c, ft_strlen(c)) && str[*j] != 0)
	{
		ft_move_next_quotes_pip(str, &n, j);
		ft_aux(str, &n, j);
		(*j)++;
		n++;
	}
	return (ft_substr(&str[((*j) - n)], 0, n));
}

static char	*gen_str2(char *str, int *j, char *c)
{
	while (str[*j] != '\0')
	{
		if (ft_strncmp(&(str[*j]), c, ft_strlen(c)) && str[*j] != 0)
			return (gen_string_with2(str, j, c));
		else
			(*j) = (*j) + ft_strlen(c);
	}
	return (NULL);
}

char	**special_split_launcher(char *str, char *c)
{
	int		i;
	int		j;
	int		n;
	char	**matriz;

	if (!str || !(str[0]))
		return (NULL);
	n = count_str2(str, c);
	matriz = malloc((n + 1) * sizeof(char *));
	matriz[n] = NULL;
	i = 0;
	j = 0;
	while (str[j] != '\0')
		matriz[i++] = gen_str2(str, &j, c);
	return (matriz);
}
/*
 int main(int argc, char **arg)
{
 	argc = 0;
 	ft_printf_arr(special_split_launcher("echo (((((hola", "&&"));
 	return 0 ;
}*/