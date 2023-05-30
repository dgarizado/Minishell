/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:22:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/29 18:29:32 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int ft_check_empty_pipe(void)
{
	int i;

	i = 0;

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
 * @return int 0 OK, 1 NO
 */
int	ft_check_pipes(void)
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
 * @brief Check to execute unset, export, cd
 * Check is alone or in pipes
 * execute ft_program in main followed to skip init_promt().
 * So we dont loose the changes in env and the path of the procees.
 * 
 * @return int 0 OK, 1 NO
 */
int	ft_check_exe(void)
{
	if (ft_strncmp((g_data.token1[0]), "exit", 4) == 0 || \
	ft_strncmp((g_data.token1[0]), "export", 7) == 0 || \
	ft_strncmp((g_data.token1[0]), "unset", 6) == 0 || \
	ft_strncmp((g_data.token1[0]), "cd", 2) == 0)
	{
		return (0);
	}
	return (1);
}
static int	delimiter_input(char eof, int *fd)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		write(fd[1], line, ft_strlen(line));
		if (ft_str_index_chr(line, eof) != 0)
			break ;
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (0);
}

/**
 * @brief Complete the input string unclosed with ' or " correspondent
 * 
 * @param input string from readline of main process
 * @param c the quote to be closed
 * @return char* string with closed quotes 
 */
char *ft_close_quotes_input(char *input, char c)
{
	int			pid;
	int			fd[2];
	char		buff[1000];
	ssize_t		n;
	char		*tmp;
	int			control_read;
	
	control_read = 1;
	n = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		exit (delimiter_input(c, fd));
	}
	else
	{
		wait(NULL);
		n = read(fd[0], &buff, 1000);
		//printf("VALOR N_READ %zu\n", n);
		buff[n] = '\0';
		tmp = input;
		input = ft_strjoin(input, buff);
		free(tmp);
		close (fd[1]);
		close (fd[0]);
	}
	return (input);
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
	//int	status;
	char c;

	i = 0;
	if (g_data.input == NULL || g_data.input[0] == '\0')
		return (0);
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
	//ft_printf_arr(g_data.token1);
	if (ft_check_empty_pipe() == -1)
		return (1);
	ft_check_expand();
	g_data.input_ex = ft_untoken();
	return (0);
}
