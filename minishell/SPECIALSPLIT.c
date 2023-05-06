/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPECIALSPLIT.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:27:39 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/06 02:27:40 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_dataflagstoken1 = 0; ///WATCH OUT

void	ft_printf_arr(char **new_arg)
{
	int	n;

	n = 0;
	while (new_arg[n])
	{
		printf("%s\n", new_arg[n]);
		n++;
	}
}


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

static char *gen_string_apostrophe(char *str, size_t *jj)
{
	char	flag;
	size_t	j;

	j = 0;
	flag = *str;
	j++;
	while (str[j] != flag)
		j++;
	while (str[j] != ' ' && str[j])
		j++;
	*jj = *jj + j;
	if (g_dataflagstoken1 == 0)
		return (ft_substr(&str[0], 0, j + 1));
	else
		return (ft_substr(&str[0], 1, j - 1));

}

static char *gen_matriz(char *str, size_t *j, char c)
{
	size_t	n;
	char *new_string;
	int flag;
	int x;

	flag = 0;
	x = 0;
	while(str[*j] != '\0')
	{
		if (str[*j] == '\'' || str[*j] == '"')
		{
			new_string = gen_string_apostrophe(&str[*j], j);
			(*j)++;
			return (new_string);
		}
		else if (str[*j] != c)
		{
			while(str[*j] == ' ')
				(*j)++;
			n = 0;
			while ((str[*j] != c  || flag == 1) && str[*j] != '\0')	
			{
				if (str[*j] == '\'' || str[*j] == '"')
					x++;	
				if (x == 1)
					flag = 1;
				else
					flag = 0;	
				n++;
				(*j)++;
			}
			return(ft_substr(&str[((*j) - n)], 0, n));
		}
		else
			(*j)++;
	}
	return(NULL);
}
char	**specialsplit(char *str, char c)
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
	{
		matriz[i] = gen_matriz(str, &j, c);
		i++;
	}
	return (matriz);
}

int main(void)
{
	char *str = "ABA CDC'ABA'otr 'text'";
	//char *str = "a |a'| po'rt|'camila '|'texto'";
	ft_printf_arr(specialsplit(str, ' '));
	return 0;
}
