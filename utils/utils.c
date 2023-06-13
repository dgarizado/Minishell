/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:29 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/13 17:37:52 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

int	ft_error(char *err)
{
	ft_putstr_fd(err, 2);
	return (-1);
}

/**
 * @brief Prints the error message and exits with the ret value.
 * 
 * @param s1 
 * @param s2 
 * @param s3 
 * @param ret 
 * @return int 
 */
int	ft_error_in(char *s1, char *s2, char *s3, int ret)
{
	s1 = NULL;
	s3 = NULL;
	ft_putstr_fd(RED"minishell: "RST_CLR, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	ft_putstr_fd(": No such file or directory\n"RST_CLR, 2);
	freelancer();
	ft_free_split(g_data.env);
	exit(ret);
}

/**
 * @brief Checks if there is any infile with 
 * more than two '<' characters.
 * 
 * @param i 
 * @return int 
 */
int	aux_del(int i)
{
	while (g_data.infiles[i])
	{
		if (g_data.infiles[i][1] == '<' && g_data.infiles[i][2] == '<')
		{
			printf(RED"minishell: syntax error near unexpected token \
			`<'\n"RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Replace with a space the specific characters from i 
 * to j of the str.
 * 
 * @param i 
 * @param j 
 * @param str 
 * @return int 
 */
int	delete_str(int i, int j, char *str)
{
	while (i <= j && str[i] != '\0')
	{
		str[i] = ' ';
		i++;
	}
	return (0);
}

/**
 * @brief Ignores the characters inside quotes.
 * 
 */
int	ignore_redics(char *str, int *i)
{
	int	flag;

	if (str[(*i)] == '\'' || str[(*i)] == '\"')
	{
		flag = str[(*i)];
		(*i)++;
		while (str[(*i)] != flag)
			(*i)++;
		(*i)++;
	}
	return (0);
}
