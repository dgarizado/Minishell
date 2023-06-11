/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:53:53 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/11 19:02:09 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief WHen there are more than one star in the pattern,
 * this function finds that the incoming string
 * contains the pattern between the stars.
 * @param str
 * @param i
 * @return char*
 */
char	*new_pattern(char *str, int i)
{
	char	*new_pattern;
	char	**str_array;
	char	*aux;
	int		j;

	str_array = ft_split(str, ' ');
	aux =  NULL;
	new_pattern = ft_substr(g_data.wc.end, 0, i);
	getchar();
	j = 0;
	while (str_array[j] != NULL)
	{
		if (ft_strnstr(str_array[j], new_pattern, ft_strlen(str_array[j])) != NULL)
		{
			if (aux == NULL)
				aux = ft_strdup(str_array[j]);
			else
				aux = ft_join_free(aux, str_array[j]);
		}
		j++;
	}
	free(new_pattern);
	ft_free_split(str_array);
	return (aux);
}

char	*ft_helper(char *str, char *aux)
{
	free(str);
	str = NULL;
	str = ft_strdup(aux);
	free(aux);
	aux = NULL;
	free(g_data.wc.end);
	g_data.wc.end = NULL;
	g_data.wc.end = ft_strdup(g_data.wc.end_aux);
	free(g_data.wc.end_aux);
	g_data.wc.end_aux = NULL;
	return (str);
}

char	*ft_more_stars(char *str)
{
	int		i;
	char	*aux;

	i = 0;
	aux = NULL;
	while (g_data.wc.end[i] != '\0')
	{
		if (g_data.wc.end[i] == '*')
		{
			g_data.wc.end_aux = ft_strdup(g_data.wc.end + i + 1);
			aux = new_pattern(str, i);
			break ;
		}
		i++;
	}
	if (aux != NULL)
		return (ft_helper(str, aux));

	return (str);
}

/**
 * @brief Join two strings, adding a space between them.
 * Only the first string is freed.
 * The second string is not freed. Because it is used
 * an element of an array of strings that is freed later.
 * @param s1
 * @param s2
 * @return char*
 */
char	*ft_join_free(char *s1, char *s2)
{
	char	*new_string;
	int		last;

	new_string = (char *)ft_calloc(1, ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new_string)
		return (NULL);
	new_string = ft_copyy(new_string, s1, 0);
	last = ft_strlen(s1);
	new_string[last] = ' ';
	new_string = ft_copyy(new_string, s2, last + 1);
	free(s1);
	s1 = NULL;
	return (new_string);
}
