/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPECIALSPLIT.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:51:28 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/04 14:10:15 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "./libft/libft.h"

extern t_data	g_data;
//t_data	g_data;

static int	count_str(char *str, char c)
{
	int		count;
	char	flag;

	count = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			flag = *str;
			str++;
			while (*str != flag)
				str++;
		}
		if ((*str != c && *(str + 1) == c) || \
		(*str != c && *(str + 1) == '\0'))
			count++;
		str++;
	}
	return (count);
}

static char	*gen_string_with(char *str, int *j, char c)
{
	int		n;
	char	flag;

	n = 0;
	while ((str[*j] != c) && str[*j] != 0)
	{
		if (str[*j] == '\'' || str[*j] == '"')
		{
			flag = str[*j];
			n++;
			(*j)++;
			while (str[*j] != flag)
			{
				n++;
				(*j)++;
			}
		}
		n++;
		(*j)++;
	}
	return (ft_substr(&str[((*j) - n)], 0, n));
}

unsigned char	*find_and_mark_chars(unsigned char *tmp)
{
	int		i;
	char	flag;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			flag = tmp[i];
			tmp[i++] = 254;
			while (tmp[i] != flag)
				i++;
			tmp[i] = 254;
		}
		i++;
	}
	return (tmp);
}

unsigned char	*skip_marked_chars(unsigned char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == 254)
		{
			while (tmp[i])
			{
				tmp[i] = tmp[i + 1];
				i++;
			}
			i = 0;
		}
		else
			i++;
	}
	return (tmp);
}

static char	*gen_string_without(char *str, int *j, char c)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)gen_string_with(str, j, c);
	tmp = find_and_mark_chars(tmp);
	tmp = skip_marked_chars(tmp);
	return ((char *)tmp);
}

static char	*gen_str(char *str, int *j, char c)
{
	while (str[*j] != '\0')
	{
		if (str[*j] != c && str[*j] != 0)
		{
			if (g_data.flags.token1 == 0)
				return (gen_string_with(str, j, c));
			else
				return (gen_string_without(str, j, c));
		}
		else
			(*j)++;
	}
	return (NULL);
}

char	**specialsplit(char *str, char c)
{
	int		i;
	int		j;
	int		n;
	char	**matriz;
	static int		alloc = 0;
	
	if (!str || !(str[0]))
		return (NULL);
	// printf("STR ENTERED: %s, %p\n", str, str);
	n = count_str(str, c);
	// printf("AFTER COUNT: %s, %p\n", str, str);
	matriz = malloc((n + 1) * sizeof(char *));
	alloc++;
	// printf(BLUE"\nallocated for: %s : %p : %d :flag %d: looking for '%c': n is %d\n"RST_CLR, str, matriz, alloc, g_data.flags.token1, c, n);
	matriz[n] = NULL;
	i = 0;
	j = 0;
	while (str[j] != '\0')
		matriz[i++] = gen_str(str, &j, c);
	return (matriz);
}

/*
int main(int argc, char **arg, char **e)
{
	argc = 0;
	arg = 0;
	char *str = "\"5'6asd'\" '' o''''tr \"'\" a''";
	char **matriz;
	//char *str = "\"'1234'\" \"5'6asD'\"otra";
	g_data.env = e;

	g_data.flags.token1 = 1;
	matriz = split_beta(str, ' ');
	ft_printf_arr(split_beta(str, ' '));
	ft_abort(matriz, ft_arrlen(matriz));
	system("leaks a.out");
	return 0;
}
*/