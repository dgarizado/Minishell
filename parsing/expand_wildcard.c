/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:03:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/09 17:23:30 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

void	ft_checkquotess(int i, int *j, int *flag_quote, int *flag_expand)
{
	g_data.flags.wildcard_expanded = 0;
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
 * @brief This function replaces the character c
 * with the character r in the string str.
 * @param str 
 * @param c 
 * @param r 
 * @return int 
 */
int	ft_replace_chr(char *str, char c, char r)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = r;
		i++;
	}
	return (0);
}

/**
 * @brief This function checks if there is $ or *
 * in each token. Then expand it if it is
 * not enclosed by single quotes.
 * 
 * @return int 
 */
int	ft_check_wildcard(int i, int j, int flag_expand, int flag_quote)
{
	i = 0;
	while (g_data.token1[i] != NULL)
	{
		j = 0;
		flag_quote = 0;
		flag_expand = 1;
		while (g_data.token1[i][j] != '\0')
		{	
			ft_checkquotess(i, &j, &flag_quote, &flag_expand);
			if (flag_expand == 0)
				j = ft_de_oca_a_oca(i, j, &flag_quote, &flag_expand);
			if (g_data.token1[i][j] == '*')
			{
				ft_expand_star(i, j);
				flag_quote = 0;
				flag_expand = 1;
				j = -1;
			}
			j++;
			if (g_data.flags.wildcard_expanded == 1)
				break ;
		}
		i++;
	}
	return (0);
}
