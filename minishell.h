/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/17 20:52:02 by dgarizad         ###   ########.fr       */
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
# define INFILEE "<"
# define OUTFILEE ">"
# define APPENDD ">>"
# define HEREDOCC "<<"

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
	OUTFILE,
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
	char	redirector[2];
	char	*input;
	char	*input_ex;
	char	**token1;
	char	**token2;
	char	**pipes;
	char	**commands;
	char	**infiles;//erase
	char	**outfiles;//erase
	char	**env;
	int		pipes_nbr;
	int		flag_env;
	t_flags	flags;
	pid_t	mainpid;
	int		child_status;
}	t_data;

//MAIN
int		init_prompt(void);

//BUILTS IN
int		ft_pwd(void);
int		ft_exit(void);
int		msg_error(char *s1, char *s2);
int		str_error(char *s1, char *s2);
char	*swap_arg(char *s1, char *s2);
int		chdir_swap(char *new_path, char **arr);//ls| cd
int 	msg_error(char *s1, char *s2);
int 	str_error(char *s1, char *s2);
char 	*swap_arg(char *s1, char *s2);
int 	chdir_swap(char *new_path, char **arr);
int		ft_cd(char **arr);
char	**ft_abort(char **new_array, unsigned int i);
int		ft_export(char **arr);
char 	**ft_export_unset(char **arr, char ***static_env);

//INIT
int		init(char **env);

//LEXIC
int		ft_lexic(char *input);
bool	is_enclosed(const char *str, int idx);
int		ft_parcerito(void);

//PIPEX SPLIT
char	**pipexsplit(char *str);

//UTILS
void	ft_error(char *err);

//EXPAND
int		ft_check_expand(void);

//UNTOKEN
char	*ft_untoken(void);
char	*ft_join(char *s1, char *s2);

//PROGRAM
int		ft_program(char *str);

//WEDDING PLANNER
int		wedding_planner(void);

#endif
