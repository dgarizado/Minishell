/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:25:47 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/20 22:54:26 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

char *delimiter(int i, char *eof)
{
	char	*line;
	char	*tmp;
	char	*aux;
	
	i =0;
	tmp = ft_strdup("");
	while (42)
		{
			line = readline("> ");
			if (ft_strncmp(line, eof, ft_strlen(line)) == 0)
			{
				free(line);
				break ;
			}
			aux = tmp;
			tmp = ft_strjoin(tmp, line);
			free(aux);
			aux = tmp;
			tmp = ft_strjoin(line, "\n");
			free(aux);
			free(line);
		}
	return (line);
}

void	ft_here_doc(int i, char *eof)
{
	char	*heredoc;
	int		pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		heredoc = delimiter(i, eof);
		exit(0);
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
int	infiles(void)
{
	int		i;
	char	*eof;
	
	i = 0;
	printf("infiles\n");
	while (g_data.infiles[i])
	{
		if (g_data.infiles[i][1] == '<')
		{
			eof = ft_strtrim(g_data.infiles[i], "<");		
			ft_here_doc(i, eof);
			g_data.flags.here_doc = 1;
			if (g_data.infiles[i + 1] == NULL)
				break ;
			else
				free(eof);
		}
		g_data.fd_in = open(g_data.infiles[i], O_RDONLY);
		// if (g_data.fd_in == -1)
		// 	return (ft_error("minishell: ", g_data.infiles[i], ": No such file or directory\n", 1));
		g_data.flags.here_doc = 0;
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
		infiles();
	return (0);
}