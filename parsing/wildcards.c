/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:34:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/10 12:51:30 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

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
	int	flag;
	char	*aux;
	
	i = 0;
	flag = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			if (i == 0)
				flag = 1;
			else if (pattern[i + 1] == '\0')
				flag = 2;
			else
				flag = 3;
		}
		i++;
	}

	return (0);
}

/**
 * @brief This function search for matches in the
 * directory and returns a string with the matches.
 * 
*/
char	*strinder(char *str, char *pattern)
{
	printf(YELLOW"TO find = '%s' %zuin :\n '%s'\n"RST_CLR".\n"RST_CLR, pattern, ft_strlen(pattern), str);
	getchar();
	char	**str_array;
	char	*aux;
	char	*aux2;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	j = 0;
	k = 0;
	aux = NULL;
	aux2 
	str_array = ft_split(str, '\n');
	while (str_array[i] != NULL)
	{
		printf("str_array[%d] = '%s'\n", i, str_array[i]);
		if (ft_strncmp(str_array[i], pattern, ft_strlen(pattern) - 1) == 0)
		{
			if (aux == NULL)
				aux = ft_strdup(str_array[i]);
			else
				aux = ft_strjoin(aux, str_array[i]);
			aux = ft_strjoin(aux, " ");
		}
		i++;
	}
	printf("aux = '%s'\n", aux);
	getchar();
	return("JOKER");
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
	strinder(strdup(buffer), aux);
	return (strdup(buffer));
}

/**
 * @brief This function concatenates the string
 * ls with the wildcard pattern. It is used in execve
 * there is a space between ls and the wildcard pattern.
 */ //CHECKPOINT
char	*concat_ls(char *str)
{
	char	*ls;
	char	*aux;

	ls = ft_strdup("ls -d ");
	aux = ft_strjoin(ls, str);
	free(ls);
	ls = NULL;
	return (aux);
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
	ft_replace_chr(g_data.token1[i], '\n', ' ');
	close(fd[0]);
	printf(YELLOW"token1[%d] = %s\n"RST_CLR".\n"RST_CLR, i, g_data.token1[i]);
	getchar();
	if (g_data.token1[i][0] == '\0')
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
	}
	return (0);
}
// END OF WILDCARD FUNCTIONS!!!!!!!!!