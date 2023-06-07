/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:36:14 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/07 18:09:19 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

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

int	count_str(char *str, char c)
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
