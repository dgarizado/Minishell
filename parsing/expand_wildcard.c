/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:03:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/07 21:48:36 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

/**
 * @brief Trims the string that contains $ARG
 * in order to search it in the ENV list. 
 * @param i 
 * @param j 
 * @param lenvar 
 * @return char* 
 */
static char	*ft_getenvv(int i, int j, int lenvar)
{
	char	*var;
	char	*aux;
	int		n;

	aux = NULL;
	var = ft_substr(g_data.token1[i], j + 1, lenvar - 1);
	n = 0;
	if (g_data.token1[i][j + 1] == '?')
		return (ft_itoa(g_data.child_status));
	while (g_data.env[n])
	{
		if (ft_strncmp(g_data.env[n], var, ft_strlen(var)) == 0 \
		&& g_data.env[n][ft_strlen(var)] == '=')
			break ;
		n++;
	}
	if (g_data.env[n])
		aux = ft_strdup(&g_data.env[n][ft_strlen(var) + 1]);
	if (!aux)
	{
		aux = ft_calloc(1, 1);
	}
	free (var);
	var = NULL;
	return (aux);
}

/**
 * @brief Calculates the len of the $VAR 
 * Is used for the expantion.
 * if there is a $ in the string, it wont count it
 *
 * @param i 
 * @param j 
 * @return int 
 */
static int	auxx(int i, int j)
{
	int	k;

	k = 0;
	if (g_data.token1[i][j + 1] == '?')
		return (2);
	while (ft_isalnum((char)g_data.token1[i][j]) == 1 \
	|| g_data.token1[i][j] == '$')
	{
		j++;
		k++;
		if (g_data.token1[i][j] == '$')
			break ;
	}
	return (k);
}

/**
 * @brief This function finds the call of $ 
 * and expands it into the proper string. 
 * @param i 
 * @param j 
 * @return int 
 */
int	ft_expandd(int i, int j)
{
	int		lenvar;
	char	*str1;
	char	*str2;
	char	*expand;

	str1 = ft_substr(g_data.token1[i], 0, j);
	lenvar = auxx(i, j);
	expand = ft_getenvv(i, j, lenvar);
	str2 = ft_strjoin(str1, expand);
	free(expand);
	expand = NULL;
	free(str1);
	str1 = NULL;
	str1 = ft_substr(g_data.token1[i], j + lenvar, ft_strlen(g_data.token1[i]));
	free(g_data.token1[i]);
	g_data.token1[i] = NULL;
	g_data.token1[i] = ft_strjoin(str2, str1);
	free(str1);
	str1 = NULL;
	free(str2);
	str2 = NULL;
	return (0);
}

void	ft_checkquotess(int i, int *j, int *flag_quote, int *flag_expand)
{
	if (g_data.token1[i][*j] == '\"' && *flag_quote == 0)
		*flag_quote = 1;
	else if (g_data.token1[i][*j] == '\"' && *flag_quote == 1)
		*flag_quote = 0;
	else if (g_data.token1[i][*j] == '\'' && *flag_quote == 0)
		*flag_expand = 0;
	if (*flag_quote == 1)
		*flag_expand = 1;
}
// FROM HERE IS WILDCARD FUNCTIONS !!!!!!!!!!!!!!!

/**
 * @brief This function replaces the character c
 * with the character r in the string str.
 * @param str 
 * @param c 
 * @param r 
 * @return int 
 */
int ft_replace_chr(char *str, char c, char r)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = r;
		i++;
	}
	return (0);
}

char *ft_read_pipe(int fd)
{
	char buffer[1024];
	int i;
	
	i = read(fd, buffer, 1024);
	buffer[i] = '\0';
	//printf(BLUE"BUFFER: \n'%s'\n"RST_CLR".\n"RST_CLR, buffer);
	return (strdup(buffer));
}

/**
 * @brief This function concatenates the string
 * ls with the wildcard pattern. It is used in execve
 * there is a space between ls and the wildcard pattern.
 */
char *concat_ls(char *str)
{
	char *ls;
	char *aux; //LEAK?

	ls = ft_strdup("ls ");
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
int create_cmd_array(int i)
{
	char **cmd_array; //LEAK?
	
	cmd_array = malloc(sizeof(char *) * 4);
	cmd_array[0] = ft_strdup("/bin/sh");
	cmd_array[1] = ft_strdup("-c");
	cmd_array[2] = concat_ls(g_data.token1[i]);
	cmd_array[3] = NULL;

	int error_fd = open("error.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (error_fd == -1) {
        perror("open");
        return 1;
    }

    // Redirect stderr to the error_fd file descriptor
    if (dup2(error_fd, STDERR_FILENO) == -1) {
        perror("dup2");
        close(error_fd);
        return 1;
    }
	execve("/bin/sh", cmd_array, NULL);
	return (0);
	//return (cmd_array);
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
int ft_expand_star(int i, int j)
{
	// char	*str1;
	// char	*str2;
	// char	*expand;
	int 	pid;
	int		fd[2];
	// char	**cmd_array;
	
	// printf(YELLOW"\nFound a * in i %d, j %d\n"RST_CLR".\n"RST_CLR, i, j);
	// printf(YELLOW"Token before expand: "RST_CLR"%s\n", g_data.token1[i]);
	j = 0;
	//getchar();
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		// close(fd[1]);
		create_cmd_array(i);
		// execve("/bin/ls", cmd_array, NULL);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		unlink("error.log");
		free(g_data.token1[i]);
		g_data.token1[i] = ft_read_pipe(fd[0]);
		ft_replace_chr(g_data.token1[i], '\n', ' ');
		close(fd[0]);
		// printf(YELLOW"Token after expand: "RST_CLR"'%s'\n", g_data.token1[i]);
	}
	//exit(0);
	return (0);
}
// END OF WILDCARD FUNCTIONS!!!!!!!!!

/**
 * @brief This function checks if there is $ or *
 * in each token. Then expand it if it is
 * not enclosed by single quotes.
 * 
 * @return int 
 */ //CHECKPOINT!!!!!!!!!
int	ft_check_wildcard(int i, int j, int flag_expand, int flag_quote)
{
	i = 0;
	while (g_data.token1[i] != NULL)
	{
		j = 0;
		flag_quote = 0;
		flag_expand = 1;
		while (g_data.token1[i][j] != '\0')
		{	
			ft_checkquotess(i, &j, &flag_quote, &flag_expand);
			if (flag_expand == 0)
				j = ft_de_oca_a_oca(i, j, &flag_quote, &flag_expand);
			if (g_data.token1[i][j] == '*')
			{
				ft_expand_star(i, j);
				flag_quote = 0;
				flag_expand = 1;
				j = -1;
			}
			j++;
		}
		i++;
	}
	return (0);
}
