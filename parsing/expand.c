/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:03:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/07 18:02:38 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief Trims the string that contains $ARG
 * in order to search it in the ENV list. 
 * @param i 
 * @param j 
 * @param lenvar 
 * @return char* 
 */
static char	*ft_getenv(int i, int j, int lenvar)
{
	char	*var;
	char	*aux;
	int		n;

	aux = NULL;
	var = ft_substr(g_data.token1[i], j + 1, lenvar - 1);
	n = 0;
	if (g_data.token1[i][j + 1] == '?')
		return (ft_itoa(g_data.child_status));
	while (g_data.env[n])
	{
		if (ft_strncmp(g_data.env[n], var, ft_strlen(var)) == 0 \
		&& g_data.env[n][ft_strlen(var)] == '=')
			break ;
		n++;
	}
	if (g_data.env[n])
		aux = ft_strdup(&g_data.env[n][ft_strlen(var) + 1]);
	if (!aux)
	{
		aux = ft_calloc(1, 1);
	}
	free (var);
	var = NULL;
	return (aux);
}

/**
 * @brief Calculates the len of the $VAR 
 * Is used for the expantion.
 * if there is a $ in the string, it wont count it
 *
 * @param i 
 * @param j 
 * @return int 
 */
static int	aux(int i, int j)
{
	int	k;

	k = 0;
	if (g_data.token1[i][j + 1] == '?')
		return (2);
	while (ft_isalnum((char)g_data.token1[i][j]) == 1 \
	|| g_data.token1[i][j] == '$')
	{
		j++;
		k++;
		if (g_data.token1[i][j] == '$')
			break ;
	}
	return (k);
}

/**
 * @brief This function finds the call of $ 
 * and expands it into the proper string. 
 * @param i 
 * @param j 
 * @return int 
 */
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
	free(expand);
	expand = NULL;
	free(str1);
	str1 = NULL;
	str1 = ft_substr(g_data.token1[i], j + lenvar, ft_strlen(g_data.token1[i]));
	free(g_data.token1[i]);
	g_data.token1[i] = NULL;
	g_data.token1[i] = ft_strjoin(str2, str1);
	free(str1);
	str1 = NULL;
	free(str2);
	str2 = NULL;
	return (0);
}

void	ft_checkquotes(int i, int *j, int *flag_quote, int *flag_expand)
{
	if (g_data.token1[i][*j] == '\"' && *flag_quote == 0)
		*flag_quote = 1;
	else if (g_data.token1[i][*j] == '\"' && *flag_quote == 1)
		*flag_quote = 0;
	else if (g_data.token1[i][*j] == '\'' && *flag_quote == 0)
		*flag_expand = 0;
	if (*flag_quote == 1)
		*flag_expand = 1;
}

/**
 * @brief This function checks if there is $ 
 * in each token. Then expand it if it is
 * not enclosed by single quotes.
 * 
 * @return int 
 */
int	ft_check_expand(int i, int j, int flag_expand, int flag_quote)
{
	i = 0;
	while (g_data.token1[i] != NULL)
	{
		j = 0;
		flag_quote = 0;
		flag_expand = 1;
		while (g_data.token1[i][j] != '\0')
		{	
			ft_checkquotes(i, &j, &flag_quote, &flag_expand);
			if (flag_expand == 0)
				j = ft_de_oca_a_oca(i, j, &flag_quote, &flag_expand);
			if (g_data.token1[i][j] == '$')
			{
				ft_expand(i, j);
				flag_quote = 0;
				flag_expand = 1;
				j = -1;
			}
			j++;
		}		
		i++;
	}
	return (0);
}
