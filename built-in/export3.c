/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:56:51 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/07 17:59:49 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

char	**ft_gen_new_arr(char *str_parsed)
{
	char	**new_env;
	int		len_env;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (str_parsed == NULL)
		return (NULL);
	len_env = ft_arrlen(g_data.env);
	new_env = (char **)malloc(sizeof(char *) * (len_env + 2));
	while (i < len_env)
	{
		new_env[i] = ft_strdup(g_data.env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(str_parsed);
	new_env[i] = NULL;
	return (new_env);
}
