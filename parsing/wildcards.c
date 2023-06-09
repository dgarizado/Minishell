/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:34:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/09 17:24:07 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief This function reads the pipe and returns
 * the string read.
 * @param fd 
 * @return char* 
 */
char	*ft_read_pipe(int fd)
{
	char	buffer[1024];
	int		i;

	i = read(fd, buffer, 1024);
	buffer[i] = '\0';
	return (strdup(buffer));
}

/**
 * @brief This function concatenates the string
 * ls with the wildcard pattern. It is used in execve
 * there is a space between ls and the wildcard pattern.
 */
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

	cmd_array = malloc(sizeof(char *) * 4);
	cmd_array[0] = ft_strdup("/bin/bash");
	cmd_array[1] = ft_strdup("-c");
	cmd_array[2] = concat_ls(g_data.token1[i]);
	cmd_array[3] = NULL;
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
	execve("/bin/bash", cmd_array, NULL);
	ft_free_split(cmd_array);
	return (0);
}

int	ft_aux(int i, int *fd, char *aux)
{
	wait(NULL);
	close(fd[1]);
	free(g_data.token1[i]);
	g_data.token1[i] = ft_read_pipe(fd[0]);
	ft_replace_chr(g_data.token1[i], '\n', ' ');
	close(fd[0]);
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