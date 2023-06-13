/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:18:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/13 15:11:46 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

char	**end_matchs_aux(char *str)
{
	char	**str_array;

	if (g_data.wc.type == 1)
		str_array = ft_split(str, '\n');
	else
		str_array = ft_split(str, ' ');
	return (str_array);
}

/**
 * @brief Search for matches at the end of each
 * file name.
 * Returns a string with the matches separated by spaces.
 * @param str 
 * @return char* 
 */
char	*end_matchs(char *str)
{
	char	**str_array;
	char	*aux;
	int		i;

	i = 0;
	aux = NULL;
	if (str == NULL)
		return (str);
	str = ft_more_stars(str);
	str_array = end_matchs_aux(str);
	while (str_array[i] != NULL)
	{
		if (ft_rstrncmp(str_array[i], g_data.wc.end, \
		ft_strlen(g_data.wc.end)) == 0)
		{
			if (aux == NULL)
				aux = ft_strdup(str_array[i]);
			else
				aux = ft_join_free(aux, str_array[i]);
		}
		i++;
	}
	ft_free_split(str_array);
	free(str);
	return (aux);
}

/**
 * @brief Search for matches at the beginning of each
 * file name.
 * Returns a string with the matches separated by spaces.
 * @param str 
 * @return char* 
 */
char	*start_matchs(char *str)
{
	char	**str_array;
	char	*aux;
	int		i;

	i = 0;
	aux = NULL;
	if (g_data.wc.start == NULL)
		return (str);
	str_array = ft_split(str, '\n');
	while (str_array[i] != NULL)
	{
		if (ft_strncmp(str_array[i], g_data.wc.start, \
		ft_strlen(g_data.wc.start)) == 0)
		{
			if (aux == NULL)
			{
				aux = ft_strdup(str_array[i]);
			}
			else
				aux = ft_join_free(aux, str_array[i]);
		}
		i++;
	}
	ft_free_split(str_array);
	return (aux);
}

char	*strinder_aux(char *str)
{
	char	*aux;
	char	*aux2;

	aux = start_matchs(str);
	aux2 = end_matchs(aux);
	free(str);
	aux = NULL;
	free(g_data.wc.start);
	g_data.wc.start = NULL;
	free(g_data.wc.end);
	g_data.wc.end = NULL;
	return (aux2);
}

/**
 * @brief This function search for matches in the
 * directory and returns a string with the matches.
 *
*/
char	*strinder(char *str, char *pattern)
{
	char	*aux;

	aux = NULL;
	analyze_pattern(pattern);
	if (g_data.wc.type == 2)
	{
		aux = start_matchs(str);
		free(str);
		str = NULL;
		free(g_data.wc.start);
		g_data.wc.start = NULL;
		return (aux);
	}
	if (g_data.wc.type == 1)
	{
		aux = end_matchs(str);
		free(g_data.wc.end);
		g_data.wc.end = NULL;
		return (aux);
	}
	if (g_data.wc.type == 3)
		return (strinder_aux(str));
	return (NULL);
}
