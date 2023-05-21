/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:25:47 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/21 23:29:46 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

//CHECKPOINT

/**
 * @brief Here we write to the pipe the content of here_doc
 * the parent will read from the pipe and any command will be executed
 * @param i 
 * @param eof 
 * @return char* 
 */
int *delimiter(char *eof, int *fd)
{
	char	*line;
	
	printf(BLUE"\ndelimiter\n"RST_CLR);
	//dup2(fd[1], STDOUT_FILENO);
	while (42)
		{
			line = readline("> ");
			if (ft_strncmp(line, eof, ft_strlen(line)) == 0 && ft_strlen(line) == ft_strlen(eof))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
	return (0);
}

void	ft_here_doc(char *eof)
{
	int		pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		delimiter(eof, fd);
		exit (0);
	}
	else
	{
		close (fd[1]);
		close (fd[0]); //WTF... IT WORKS WITHOUT THIS LINE OR WITH IT
		dup2(fd[0], STDIN_FILENO);
		waitpid (pid, NULL, 0);
		g_data.fd_in = fd[0];
	}
}

/**
 * @brief Analizes infiles array
 * open all the infiles and save the 
 * last fd in g_data.fd_in
 * checks if there is a here_doc call when 
 * there are "<<" in the infile name
 * adn calls the ft_here_doc function
 * @return int 
 */
int	infiles_doc(void)
{
	int		i; 
	char	*eof; //MEMORY LEAK
	
	i = 0;
	printf(YELLOW"\ninfiles"RST_CLR".\n");
	ft_printf_arr(g_data.infiles);
	while (g_data.infiles[i])
	{
		if (g_data.infiles[i][1] == '<' && g_data.infiles[i][2] != '<') 
		{
			printf(BLUE"\nhere_doc\n"RST_CLR);
			eof = ft_strtrim(g_data.infiles[i], "< ");
			printf("eof = '%s'\n", eof);
			ft_here_doc(eof);
			g_data.flags.here_doc = 1;
			if (g_data.infiles[i + 1] == NULL)
				break ;
			else
				free(eof);
		}
		g_data.fd_in = open(g_data.infiles[i], O_RDONLY);
		g_data.flags.here_doc = 0;
		i++;
	}
	free(eof);
	return (0);
}

int	ft_error_in(char *s1, char *s2, char *s3, int ret)
{
	ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	exit (ret);
}

/**
 * @brief Checks if all infiles are valid, only with one '<'
 * 
 * @return int 
 */
int	check_infiles(void)
{
	int	i;
	int	fd;

	i = 0;
	while (g_data.infiles[i])
	{
		if (g_data.infiles[i][1] != '<')
			i++;
		fd = open(g_data.infiles[i], O_RDONLY);
		if (fd == -1)
			return (ft_error_in(RED"minishell: ", (g_data.infiles[i] + 1), \
			": No such file or directory\n"RST_CLR, 1));
		i++;
	}
	return (0);
}

/**
 * @brief Analizes infiles and outfiles
 * creates and reads the respective files
 * if there are more than one infile or outfile 
 * it will create all but only read the last one
 * and the last one will be the outfile for the dup2
 * @return int 
 */
int	analyze_redic(void)
{
	//printf("\nanalize_redic\n");
	if (g_data.infiles)
	{
		infiles_doc();
		//check_infiles();
	}
	return (0);
}