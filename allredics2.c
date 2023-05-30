/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allredics2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:25:47 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/30 19:51:16 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Here we write to the pipe the content of here_doc
 * the parent will read from the pipe and any command will be executed
 * @param i 
 * @param eof 
 * @return char* 
 */
int	delimiterr(char *eof, int *fd, int std_out)
{
	char	*line;

	dup2(std_out, STDOUT_FILENO);
	while (42)
	{
		line = readline("> ");
		//printf("line = %s", line);
		if (ft_strncmp(line, eof, ft_strlen(line)) == 0 \
		&& ft_strlen(line) == ft_strlen(eof))
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

/**
 * @brief Creates a sub process that will write to the pipe 
 * the content of here_doc
 * the parent will read from the pipe and any command will have
 * the content of the pipe as input.
 * The here_doc will be read only if there is no more infiles
 * @param eof 
 */
void	ft_here_docc(char *eof, int i)
{
	int		pid;
	int		fd[2];
	int		len;

	pipe(fd);
	// printf("original_std_out = %d\n", g_data.original_std_out);
	// write(g_data.original_std_out, "aaaaaaa\n", 8);
	len =  ft_arrlen(g_data.infiles);
	pid = fork();
	if (pid == 0)
	{
		// close(g_data.pipes[g_data.n_pipe -1][STDIN_FILENO]);
		dup2(g_data.original_std_in, STDIN_FILENO);
		close(fd[0]);
		exit (delimiterr(eof, fd, g_data.original_std_out));
	}
	else
	{
		waitpid (pid, NULL, 0);
		close (fd[1]);
		if (strcmp(g_data.redics[i], g_data.infiles[len - 1]) == 0) //FORBIDDEN	FUNCTION, change to ft_strcmp
			dup2(fd[0], STDIN_FILENO);
		//if (g_data.infiles[i + 1] == NULL && g_data.flags.here_doc_ret != 258) //This is an error, should be checking data.redics...
			//dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
	}
}

//CHECKPOINTVICTOR SIMPATICO
/**
 * @brief Analizes infiles array
 * open all the infiles and save the 
 * last fd in g_data.fd_in
 * checks if there is a here_doc call when 
 * there are "<<" in the infile name
 * adn calls the ft_here_docc function
 * @return int 
 */
int	infiles_docc(void)
{
	int		i;
	char	*eof; //MEMORY LEAK

	i = 0;
	while (g_data.redics[i])
	{
		if (g_data.redics[i][1] == '<' && g_data.redics[i][2] != '<')
		{
			eof = ft_strtrim(g_data.redics[i], "< ");
			if (g_data.flags.here_doc_ret != 258 || g_data.flags.here_doc_aux > i)
				ft_here_docc(eof, i);
			if (g_data.redics[i + 1] == NULL)
				break ;
			else
				free(eof);
		}
		if (g_data.redics[i][0] == '>' && g_data.flags.here_doc_ret != 258)
			ft_open_outfile(i);
		ft_openn(i);
		i++;
	}
	// if (eof) //MEMORY LEAK WH
	// 	free(eof); 
	return (0);
}

/**
 * @brief Checks if all infiles are valid, only with one '<'
 * yes, it can be done with access, but we get the same result.
 * @return int 
 */
int	check_infiless(void)
{
	int		i;
	int		fd;
	char	*aux;

	i = 0;
	while (g_data.infiles[i])
	{
		while (g_data.infiles[i] != NULL && g_data.infiles[i][1] == '<')
			i++;
		if (g_data.infiles[i] == NULL)
			break ;
		aux = ft_strtrim(g_data.infiles[i], "< ");
		fd = open(aux, O_RDONLY);
		if (fd == -1)
		{
			//free(aux);
			return (ft_error_in(RED"\nminishell: ", (g_data.infiles[i] + 1), \
			": No such file or directory\n"RST_CLR, 1));
		}
		close(fd);
		//free(aux);
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
int	analyze_redicc(void)
{
	if (g_data.redics)
	{
		aux_dell(0);
		infiles_docc();
		if (g_data.flags.here_doc_ret == 258)
			exit (g_data.flags.here_doc_ret);
		if (g_data.infiles)
			check_infiless();
	}
	return (0);
}
