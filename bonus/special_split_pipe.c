/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:35:30 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/13 19:34:16 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

static int	count_str3(char *str, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = ft_move_next_quotes(str, i);
		i = ft_move_next_priority_quote(str, i);
		if (str[i] == '|' && str[i + 1] == '|')
		{
			i++;
			i++;
		}
		if ((str[i] != c && str[i + 1] == c && str[i + 2] != c) \
		|| (str[i] != c && str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*gen_string_with_pip(char *str, int *j)
{
	int		n;
	int		tmp;

	n = 0;
	while ((str[*j] != '|' && str[*j] != 0))
	{
		ft_move_next_quotes_pip(str, &n, j);
		tmp = *j;
		*j = ft_move_next_priority_quote(str, *j);
		n = n + (*j - tmp);
		n++;
		(*j)++;
		if (str[*j] == '|' && str[*j + 1] == '|')
		{
			n += 2;
			(*j) += 2;
		}
	}
	return (ft_substr(&str[((*j) - n)], 0, n));
}

static char	*gen_str_pip(char *str, int *j)
{
	while (str[*j] != '\0')
	{
		if (str[*j] != '|' && str[*j] != 0)
		{
			return (gen_string_with_pip(str, j));
		}
		else
			(*j)++;
	}
	return (NULL);
}

char	**special_split_pipe(char *str)
{
	int		i;
	int		j;
	int		n;
	char	**matriz;

	if (!str || !(str[0]))
		return (NULL);
	n = count_str3(str, '|');
	if (n == 0)
		return (NULL);
	if (n == 0)
		return (NULL);
	matriz = malloc((n + 1) * sizeof(char *));
	matriz[n] = NULL;
	i = 0;
	j = 0;
	while (str[j] != '\0')
		matriz[i++] = gen_str_pip(str, &j);
	return (matriz);
}
