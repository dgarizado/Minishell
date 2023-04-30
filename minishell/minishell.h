/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/30 22:25:28 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PRAMPT "minishell$>"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "./libft/libft.h"
# include "errno.h"

typedef enum	e_redirections
{
	INFILE,
	DELIMITER,
	OUTFILE,
	APPEND,
	REDIR_COUNT
} t_redirections;

typedef enum	e_separators
{
	PIPE,
	AND,
	OR,
	SEP_COUNT
} t_separators;

typedef struct s_data
{
	char	separator[3];
	char	redirector[4];
	char	*input;
	char	**token1;
	pid_t	mainpid;
	int		child_status;
		
}	t_data;

//BUILTS IN
int		ft_pwd(void);
int		ft_cd(char *newdir);
int		ft_exit(void);
//INIT
int		init(void);

 //LEXIC
int		ft_lexic(char *input);

//PIPEX SPLIT
char	**pipexsplit(char *str);

//UTILS
void	ft_error(char *err);

#endif
