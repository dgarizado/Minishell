/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/16 18:26:33 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PRAMPT "mini🐢$>"
# define WHITE   "\x1b[1;37m"
# define YELLOW "\x1b[1;33m"
# define BLUE "\x1b[1;36m"
# define PINK "\x1b[1;35m"
# define RST_CLR    "\x1b[0m"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "./libft/libft.h"
# include "errno.h"
# include <stdbool.h>

typedef enum e_redirections
{
	INFILE,
	DELIMITER,
	OUTFILE,
	APPEND,
	REDIR_COUNT
}	t_redirections;

typedef enum e_separators
{
	PIPE,
	AND,
	OR,
	SEP_COUNT
}	t_separators;

typedef struct s_flags
{
	int	token1;
}	t_flags;

typedef struct s_data
{
	char	separator[3];
	char	redirector[4];
	char	*input;
	char	*input_ex;
	char	**token1;
	char	**token2;
	t_flags	flags;
	pid_t	mainpid;
	int		child_status;
}	t_data;

//MAIN
int		init_prompt(void);

//BUILTS IN
int		ft_pwd(void);
int		ft_exit(void);
int 	msg_error(char *s1, char *s2);
int 	str_error(char *s1, char *s2);
char 	*swap_arg(char *s1, char *s2);
int 	chdir_swap(char *new_path, char **arr);
int		ft_cd(char **arr);
char	**ft_abort(char **new_array, unsigned int i);
int		ft_export(char **arr);
char 	**ft_export_unset(char **arr, char ***static_env);

//INIT
int		init(void);

//LEXIC
int		ft_lexic(char *input);
bool	is_enclosed(const char *str, int idx);

//PIPEX SPLIT
char	**pipexsplit(char *str);

//UTILS
void	ft_error(char *err);

//EXPAND
int		ft_check_expand(void);

//UNTOKEN
char	*ft_untoken(void);

#endif
