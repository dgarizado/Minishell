/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:22:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/05 18:29:30 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_data	g_data;
extern t_data	g_data;

int ft_check_empty_pipe(void)
{
	int i;

	i = 0;

	printf("\nTOKEN1: %s, %p\n", g_data.token1[0], g_data.token1);
	// getchar();
	while(g_data.token1[i + 1] )
	{
		if ((g_data.token1[i][0] == '|' && g_data.token1[i][1] == '\0' && g_data.token1[i + 1][0] == '|' && g_data.token1[i + 1][1] == '\0') ||  (g_data.token1[i][ft_strlen(g_data.token1[i]) - 1] == '|' && g_data.token1[i + 1][0] == '|'))
		{
			str_error("minishell" ,"syntax error near unexpected token `|'");
			return (-1);
		}
		i++;
	}
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
 * @brief Check if there are pipes not enclosed in '' or "".
 * 
 * @return int 0 when there is at least 1 pipe, 
 * 1 for no pipes.
 */
int	ft_check_pipes(void)
{
	char	**arr;
	int		n;

	// printf("NOT FREEING HERE: %p\n", g_data.input_ex);
	arr = specialsplit(g_data.input_ex, '|');
	// printf(GREEN"ALLOCATED HERE: %p, %s, %d nodes\n"RST_CLR"."RST_CLR, arr, arr[0], ft_arrlen(arr));
	if (ft_arrlen(arr) > 1)
		n = 0;
	else
		n = 1;
	//ft_abort(arr, ft_arrlen(arr));
	ft_free_split(arr);
	if (ft_strncmp((g_data.token1[0]), "exit", ft_strlen(g_data.token1[0])) == 0)
		free(g_data.input_ex); //WTF IS THIS
	// printf(RED"CHEKCK PIPES IS: %d\n"RST_CLR"."RST_CLR"\n"RST_CLR, n);
	return (n);
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
int	ft_check_exe(void)
{
	// printf(GREEN"CHEKCK EXE IS: '%s'."RST_CLR, g_data.token1[0]);
	// getchar();
	if (ft_strncmp((g_data.token1[0]), "exit", ft_strlen(g_data.token1[0])) == 0 || \
	ft_strncmp((g_data.token1[0]), "export", 7) == 0 || \
	ft_strncmp((g_data.token1[0]), "unset", 6) == 0 || \
	ft_strncmp((g_data.token1[0]), "cd", 2) == 0)
	{
		// printf(RED"CHECK EXE IS: %d\n"RST_CLR"."RST_CLR, 0);
		return (0);
	}
	// printf(RED"CHEKCK EXE IS: %d\n"RST_CLR"."RST_CLR, 1);
	return (1);
}

/**
 * @brief Checks if the string is only spaces
 * 
 * @param str 
 * @return int 
 */
int is_space(char *str)
{
	int	i;

	i = 0;

	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' &&\
		 str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Sets the flag to determine if there are heredocs 
 * in order to have or not concurrency in pipex.
 * Ignore the heredocs if they are inside quotes.
 * @param str 
 * @return int 
 */
void	check_heredocs(char *str)
{
	int	i;
	int flag;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] =='\'' || str[i] == '\"')
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
				i++;
			i++;
		}
		if (str[i] == '<' && str[i + 1] == '<')
		{
			g_data.flags.concurrency = 1;
			break;
		}
		i++;
	}
}

/**
 * @brief Checks if there are unclosed  ' or ""
 * and performs a first tokenization(split by spaces) in order
 * to facilitate the expand function. The Expansion 
 * is also done here. 
 * @param input 
 * @return int if execute program return status, if not return -1 means to continue to init_promt()
 */
int	ft_lexic(void)
{
	int	i;
	char c;

	i = 0;
	if (g_data.input == NULL || g_data.input[0] == '\0' || is_space(g_data.input) == 1)
		return (1);
	while (g_data.input[i] != '\0')
	{
		if (g_data.input[i] == '\'' || g_data.input[i] == '\"' )
		{
			c = g_data.input[i];
			if (ft_is_closed(g_data.input, &i, g_data.input[i]) == 1)
				return (ft_error("unclosed quoutes\n"));
		}
		i++;
	}
	g_data.flags.token1 = 0;
	g_data.token1 = specialsplit((g_data.input), ' ');
	//printf(BLUE"token1: %p, %s\n"RST_CLR"\n"RST_CLR".", g_data.token1[0], g_data.token1[0]);
	//ft_printf_arr(g_data.token1);
	if (ft_check_empty_pipe() == -1)
		return (1);
	ft_check_expand();
	g_data.input_ex = ft_untoken();
	// printf(YELLOW"input_ex:"RST_CLR"%s, %p\n"". "RST_CLR, g_data.input_ex, g_data.input_ex);
	check_heredocs(g_data.input_ex);
	return (0);
}
