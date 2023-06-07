/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:29 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/07 16:48:27 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_de_oca_a_oca(int i, int j, int *flag_quote, int *flag_expand)
{
	j++;
	while (g_data.token1[i][j] != '\'')
		j++;
	*flag_quote = 0;
	*flag_expand = 1;
	return (j);
}

/**
 * @brief Check to execute unset, export, cd
 * Check is alone or in pipes
 * execute ft_program in main followed to skip init_promt().
 * So we dont loose the changes in env and the path of the procees.
 * 
 * @return int 0 For executing directly at current parent process, 
 * 1 for executing in a child process.
 */
static int	ft_check_exe(void)
{
	if (ft_strncmp((g_data.token1[0]), "exit", \
	ft_strlen(g_data.token1[0])) == 0 || \
	ft_strncmp((g_data.token1[0]), "export", 7) == 0 || \
	ft_strncmp((g_data.token1[0]), "unset", 6) == 0 || \
	ft_strncmp((g_data.token1[0]), "cd", 2) == 0)
	{
		return (0);
	}
	return (1);
}

/**
 * @brief Check if there are pipes not enclosed in '' or "".
 * 
 * @return int 0 when there is at least 1 pipe, 
 * 1 for no pipes.
 */
static int	ft_check_pipes(void)
{
	char	**arr;
	int		n;

	arr = specialsplit(g_data.input_ex, '|');
	if (ft_arrlen(arr) > 1)
		n = 0;
	else
		n = 1;
	ft_abort(arr, ft_arrlen(arr));
	return (n);
}

/**
 * @brief check if run ft_program in main process to save 
 * the changes of path and env.
 */
int	check_to_exe(void)
{
	if (ft_check_exe() == 0 && ft_check_pipes() == 1 \
	&& g_data.flags.concurrency == 0)
	{
		return (0);
	}
	return (1);
}

/**
 * @brief Checks if there is any infile or outfile with 
 * more than two '<' characters.
 * 
 * @param i 
 * @return int 
 */
int	aux_dell(int i)
{
	while (g_data.redics[i])
	{
		ignore_redics(g_data.redics[i], &i);
		if (g_data.redics[i][1] == '<' && g_data.redics[i][2] == '<')
		{
			printf(RED"minishell: syntax error near unexpected token `<'\n"\
			RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		if (g_data.redics[i][1] == '>' && g_data.redics[i][2] == '>')
		{
			printf(RED"minishell: syntax error near unexpected token `>'\n"\
			RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		i++;
	}
	return (i);
}
