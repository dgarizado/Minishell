/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:16:25 by vcereced          #+#    #+#             */
/*   Updated: 2023/04/30 20:42:27 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	count_words(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			str++;
			while (*str != 34 && *str != 39)
				str++;
		}
		if (*str != ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0'))
			count++;
		str++;
	}
	return (count);
}

static size_t	gen_string_apostrophe(char *str, char **matriz, size_t i)
{
	char	flag;
	size_t	j;

	j = 0;
	flag = *str;
	j++;
	while (str[j] != flag)
		j++;
	matriz[i] = ft_substr(&str[0], 0, j+1);
	return (j);
}

static void	gen_matriz(size_t *i, size_t *j, char *str, char **matriz)
{
	size_t	n;

	if (str[*j] == 34 || str[*j] == 39)
	{
		*j = (*j) + gen_string_apostrophe(&str[*j], matriz, (*i));
		(*i)++;
		(*j)++;
	}
	else if (str[*j] != ' ')
	{
		n = 0;
		while (str[*j] != ' ' && str[*j] != '\0')
		{
			(*j)++;
			n++;
		}
		matriz[(*i)] = ft_substr(&str[((*j) - n)], 0, n);
		(*i)++;
	}
	else
	{
		(*j)++;
	}
}

char	**pipexsplit(char *str)
{
	size_t	i;
	size_t	j;
	size_t	n;
	char	**matriz;

	n = count_words(str);
	matriz = ft_calloc(n + 1, sizeof(char *));
	matriz[n] = NULL;
	i = 0;
	j = 0;
	while (str[j] != '\0')
		gen_matriz(&i, &j, str, matriz);
	return (matriz);
}
