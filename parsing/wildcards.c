/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:34:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/11 19:00:12 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief Checks if the string s2 is 
 * contained at the end of the string s1.
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int ft_rstrncmp(const char *s1, const char*s2, unsigned int n)
{
	int	len1;
	int	len2;
	int	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = len1 - len2;
	if (ft_strncmp(s1 + i, s2, n) == 0)
		return (0);
	return (1);
}

/**
 * @brief Creates the wildcard pattern.
 *
 * 
 * @param pattern 
 * @param flag 
 * @return int 
 */
int create_pattern(char *pattern, int flag)
{
	int	i;

	i = 0;
	if (flag == 3)
	{
		while (pattern[i])
		{
			if (pattern[i] == '*')
			{
				g_data.wc.start = ft_substr(pattern, 0, i);
				g_data.wc.end = ft_substr(pattern, i + 1, ft_strlen(pattern));
				break ;
			}
			i++;
		}
	}
	return (0);
}

/**
 * @brief This function checks if
 * the wildcard has text before and after.
 *And deterines how to expand it.
 * @param pattern
 * @return int
 */
int	analyze_pattern (char *pattern)
{
	int	i;
	
	i = 0;
	g_data.wc.type = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			if (i == 0)
			{
				g_data.wc.end = ft_strdup(pattern + 1);
				g_data.wc.type = 1;
			}
			else if (pattern[i + 1] == '\0')
			{
				g_data.wc.start = ft_substr(pattern, 0, i);
				g_data.wc.type = 2;
			}
			else
				g_data.wc.type = 3;
		}
		i++;
	}
	create_pattern(pattern, g_data.wc.type);
	return (0);
}

/**
 * @brief Search for matches at the end of each
 * file name.
 * Returns a string with the matches separated by spaces.
 * @param str 
 * @return char* 
 */
char	*end_matchs(char *str)
{
	char	**str_array;
	char	*aux;
	int		i;
	
	i = 0;
	aux = NULL;
	if (str == NULL)
		return (str);
	str = ft_more_stars(str);
	if (g_data.wc.type == 1)
		str_array = ft_split(str, '\n');
	else
		str_array = ft_split(str, ' ');
	while (str_array[i] != NULL)
	{
		if (ft_rstrncmp(str_array[i], g_data.wc.end, ft_strlen(g_data.wc.end)) == 0)
		{
			if (aux == NULL)
				aux = ft_strdup(str_array[i]);
			else
				aux = ft_join_free(aux, str_array[i]);
		}
		i++;
	}
	ft_free_split(str_array);
	free(str);
	return (aux);
}

/**
 * @brief Search for matches at the beginning of each
 * file name.
 * Returns a string with the matches separated by spaces.
 * @param str 
 * @return char* 
 */
char *start_matchs(char *str)
{
	char	**str_array;
	char	*aux;
	int		i;
	
	i = 0;
	aux = NULL;
	if (g_data.wc.start == NULL)
		return (str);
	str_array = ft_split(str, '\n');
	while (str_array[i] != NULL)
	{
		if (ft_strncmp(str_array[i], g_data.wc.start, ft_strlen(g_data.wc.start)) == 0)
		{
			if (aux == NULL)
			{
				aux = ft_strdup(str_array[i]);
			}
			else
				aux = ft_join_free(aux, str_array[i]);
			
		}
		i++;
	}
	ft_free_split(str_array);
	return (aux);
}

/**
 * @brief This function search for matches in the
 * directory and returns a string with the matches.
 *
*/
char	*strinder(char *str, char *pattern)
{
	char	*aux;
	char	*aux2;

	aux = NULL;
	analyze_pattern(pattern);
	if (g_data.wc.type == 2)
	{
		aux = start_matchs(str);
		free(str);
		str = NULL;
		free(g_data.wc.start);
		g_data.wc.start = NULL;
		return (aux);
	}
	if (g_data.wc.type == 1)
	{
		aux = end_matchs(str);
		free(g_data.wc.end);
		g_data.wc.end = NULL;
		return (aux);
	}
	if (g_data.wc.type == 3)
	{
		aux = start_matchs(str);
		aux2 = end_matchs(aux);
		free(str);
		aux = NULL;
		free(g_data.wc.start);
		g_data.wc.start = NULL;
		free(g_data.wc.end);
		g_data.wc.end = NULL;
		return (aux2);
	}
	return(NULL);
}

/**
 * @brief This function reads the pipe and returns
 * the string read.
 * @param fd
 * @return char*
 */
char	*ft_read_pipe(int fd, char *aux)
{
	char	buffer[1024];
	int		i;

	i = read(fd, buffer, 1024);
	buffer[i] = '\0';
	return(strinder(strdup(buffer), aux));
	//return (strdup(buffer));
}

/**
 * @brief This function creates an array of strings
 * with the command sh -c as argument and ls with the
 * wildcard pattern as argument. It is used in execve
 * as command. this disables the echo of the command.
 * @return char**
 */
int	create_cmd_array(int i)
{
	char	**cmd_array;
	int		error_fd;
	i = 0;

	cmd_array = malloc(sizeof(char *) * 2);
	cmd_array[0] = ft_strdup("/bin/ls");
	cmd_array[1] = NULL;
	error_fd = open("./utils/error.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (error_fd == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(error_fd, STDERR_FILENO) == -1)
	{
		perror("dup2");
		close(error_fd);
		return (1);
	}
	execve("/bin/ls", cmd_array, NULL);
	ft_free_split(cmd_array);
	return (0);
}

int	ft_aux(int i, int *fd, char *aux)
{
	wait(NULL);
	close(fd[1]);
	free(g_data.token1[i]);
	g_data.token1[i] = ft_read_pipe(fd[0], aux);
	close(fd[0]);
	if (g_data.token1[i] == NULL)
	{
		free(g_data.token1[i]);
		g_data.token1[i] = aux;
		g_data.flags.wildcard_expanded = 1;
	}
	else
		free(aux);
	unlink("./utils/error.log");
	return (0);
}

/**
 * @brief This function finds the call of *
 * creates a fork for running the command ls with the wildcard as
 * argument in execve. The parent waits for the child to finish and
 * the child returns the string with the wildcard expanded.
 * writing it in the pipe.
 * @param i
 * @param j
 * @return int
 */
int	ft_expand_star(int i, int j)
{
	int		pid;
	int		fd[2];
	char	*aux;

	j = 0;
	pipe(fd);
	aux = ft_strdup(g_data.token1[i]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		create_cmd_array(i);
	}
	else
	{
		ft_aux(i, fd, aux);
		// memset(g_data.wc.start, 0, ft_strlen(g_data.wc.start));
		// memset(g_data.wc.end, 0, ft_strlen(g_data.wc.end));
	}
	return (0);
}
// END OF WILDCARD FUNCTIONS!!!!!!!!!