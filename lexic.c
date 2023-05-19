/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:22:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/18 01:19:11 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

/**
 * @brief Splits the already expanded input into words and 
 * stores it in data.token2.
 * Splits the expanded input by pipes so each program
 * can be identified. Stores it in data.pipes.
 * @return int 
 */
int	ft_parcerito(void)
{
	g_data.flags.token1 = 1;
	g_data.token2 = pipexsplit(g_data.input_ex); //NEEDS PROPER FREE
	g_data.flags.token1 = 0;
	g_data.pipes = ft_split(g_data.input_ex, '|'); //NEEDS PROPER FREE
	return (0);
}

/**
 * @brief Returns true if it is enclosed by '
 * fasle if not.
 * @param str 
 * @param idx 
 * @return true 
 * @return false 
 */ //CHECKPOINT
bool	is_enclosed(const char *str, int idx)
{
	bool	inside_quotes;
	int		i;

	inside_quotes = false;
	i = 0;
	while (i < idx)
	{
		if (str[i] == '\'')
		{
			inside_quotes = !inside_quotes;
		}
		i++;
	}
	return (inside_quotes);
}

/**
 * @brief checks if the " or ' has 
 * a partner that closes it. If not
 * returns 1 and its considered an error. or not?
 * @param str 
 * @param index 
 * @param c 
 * @return int 
 */
int	ft_is_closed(char *str, int *index, char c)
{
	(*index)++;
	while (str[*index] != '\0')
	{
		if (str[*index] == c)
			return (0);
		(*index)++;
	}
	return (1);
}

/**
 * @brief Checks if there are unclosed  ' or ""
 * and performs a first tokenization(split by spaces) in order
 * to facilitate the expand function. The Expansion 
 * is also done here.
 * @param input 
 * @return int 
 */
int	ft_lexic(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
		{
			if (ft_is_closed(input, &i, input[i]) == 1)
				ft_error("\nunclosed quotes!\n");
		}
		i++;
	}
	g_data.token1 = specialsplit((g_data.input), ' ');
	if (strcmp((g_data.token1[0]), "exit") == 0) // STRCMP!!
		ft_exit();
	//HARCODED DELET:
	if (strcmp((g_data.token1[0]), "export") == 0) // STRCMP!!
	{
		ft_export(g_data.token1);
		//ft_printf_arr(g_data.env);
	}
	ft_check_expand();
	g_data.input_ex = ft_untoken();
	return (0);
}
