/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:59:17 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/06 17:53:41 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Counts the number of redirections in order
 * to allocate enough strings for storing them.
 * It doesnt properly count if there is >>>>>>>
 * this can be improved. otherwise it will allocate
 * extra spaces, that wont generate errors.
 * @param str 
 * @param c 
 * @return int 
 */
int	ft_count_redic(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (str[0] == c)
		{
			count++;
			if (str[1] == c)
				str++;
		}
		str++;
	}
	return (count);
}

/**
 * @brief Aux function for norminette issues.
 * Here is finally where the redirections are stored.
 * @param i 
 * @param j 
 * @param k 
 * @param c 
 * @return int 
 */
static int	aux_aux(int *i, int *j, int *k, char c)
{
	(*j)++;
	if (g_data.str_redic[*j] == '\0' || g_data.str_redic[*j] == ' ' \
	|| g_data.str_redic[*j] == c)
	{
		if (c == '<')
			g_data.infiles[*k] = ft_substr(g_data.str_redic, *i, *j - *i);
		else
			g_data.outfiles[*k] = ft_substr(g_data.str_redic, *i, *j - *i);
		delete_str(*i, *j, g_data.str_redic);
		(*k)++;
	}
	return (0);
}

/**
 * @brief Aux function for norminette issues. 
 * Here the redirections are managed to be stored in a different array.
 *  data.infiles or data.outfiles.
 * Also here, the text for redirections is removed. 
 * @param i 
 * @param j 
 * @param k 
 * @param c 
 * @param str 
 * @return int 
 */
int	aux(int *i, int *j, int *k, char c)
{
	if (g_data.str_redic[*i] == c)
	{
		(*j) = *i + 1;
		while (g_data.str_redic[*j] == ' ' || g_data.str_redic[*j] == c)
			(*j)++;
		while (g_data.str_redic[*j] && g_data.str_redic[*j] != ' ' \
		&& g_data.str_redic[*j] != c)
		{
			aux_aux(i, j, k, c);
		}
		if (g_data.str_redic[*i + 1] == c)
			(*i)++;
	}
			(*i)++;
	return (0);
}

/**
 * @brief Get the next redic character And build the appropriate
 * string to store it.
 * 
 * @param str 
 * @param c 
 * @return char 
 */
char	get_next_redic(char *str, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 0;
	g_data.str_redic = str;
	while (str[i] != '\0')
	{
		ignore_redics(str, &i);
		aux(&i, &j, &k, c);
	}
	g_data.str_redic = NULL;
	return (0);
}
