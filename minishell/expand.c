/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:03:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/01 22:34:11 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	aux(int i, int j, char *newstr, char *expand)
{
	int	k;
	int	l;
	
	k = 0;
	j = 0;
	while (g_data.token1[i][k] != '$')
	{
		newstr[k] = g_data.token1[i][k];
		k++;
	}
	l = 0;
	while (expand[l] != '\0')
	{
		newstr[k] = expand[l];
		k++;
		l++;
	}
	newstr[k] = '"';
	return (0);
}

/**
 * @brief This function i meant to 
 * expand env variables into text. 
 * This will need a realloc and a join.
 * @param i 
 * @param j 
 * @return int 
 */
int	ft_expand(int i, int j)
{
	int	len1; 
	int	len2;
	int newlen;
	char	*newstr;
	char	*expand = "expanded!";
	
	len1 = ft_strlen(g_data.token1[i]);
	len2 = ft_strlen(expand);
	newlen = len1 + len2 -1; //-1 in this case bcause $ is one char. this has to be the len of $ARG or whatever is called.
	newstr = ft_calloc(1, newlen + 1); 
	if (!newstr)
		return (1);
	j = 0;
	aux(i, j, newstr, expand);
	printf("\ntoken: %d , has %d chars\n", i, len1);
	free(g_data.token1[i]);
	g_data.token1[i] = newstr;
	return (0);
}
/**
 * @brief This function checks if there is $
 * in each token. Then expand it if it is
 * not enclosed by single quotes.
 * 
 * @return int 
 */
int ft_check_expand(void)
{
	int i;
	int	j;

	i = 0;
	while (g_data.token1[i] != NULL)
	{
		j = 0;
		while (g_data.token1[i][j] != '\0')
		{
			if (g_data.token1[i][j] == '$' && g_data.token1[i][0] != '\'')
				ft_expand(i, j);	
			//printf("\ntoken %d has dollar \n", i);
			j++;
		}		
		i++;
	}
	return (0);
}
