/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:03:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/02 22:52:17 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

char	*ft_getenv(int i, int j, int lenvar)
{
	char	*var;
	char	*aux;

	var = ft_substr(g_data.token1[i], j + 1, lenvar - 1);
	aux = getenv(var);
	if (!aux)
	{
		aux = ft_calloc(1, 1);
	}
	var = NULL;
	free (var);
	return (aux);
}

/**
 * @brief Calculates the len of the $VAR 
 * Is used for the expantion.
 * @param i 
 * @param j 
 * @return int 
 */
int	aux(int i, int j)
{
	int	k;

	k = 0;
	while (g_data.token1[i][j] != ' ' && g_data.token1[i][j] \
	&& g_data.token1[i][j] != '\"' && g_data.token1[i][j] != '\'') //HARDCODED NEED TO BE FIXED
	{
		j++;
		k++;
	}
	return (k);
}

/**
 * @brief This function finds the call of x 
 * and expands it into the proper string. 
 * @param i 
 * @param j 
 * @return int 
 *///CHECK POINT
int	ft_expand(int i, int j)
{
	int		lenvar;
	char	*str1;
	char	*str2;
	char	*expand;

	str1 = ft_substr(g_data.token1[i], 0, j);
	lenvar = aux(i, j);
	expand = ft_getenv(i, j, lenvar);
	str2 = ft_strjoin(str1, expand);
	expand = NULL;
	free(expand);
	str1 = NULL;
	free(str1);
	str1 = ft_substr(g_data.token1[i], j + lenvar, ft_strlen(g_data.token1[i]));
	g_data.token1[i] = NULL;
	free (g_data.token1[i]);
	g_data.token1[i] = ft_strjoin(str2, str1);
	str1 = NULL;
	free(str1);
	str2 = NULL;
	free(str2);
	return (0);
}

/**
 * @brief This function checks if there is $
 * in each token. Then expand it if it is
 * not enclosed by single quotes.
 * 
 * @return int 
 */
int	ft_check_expand(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_data.token1[i] != NULL)
	{
		j = 0;
		while (g_data.token1[i][j] != '\0')
		{
			if (g_data.token1[i][j] == '$' && g_data.token1[i][0] != '\'')
				ft_expand(i, j);
			j++;
		}		
		i++;
	}
	return (0);
}
