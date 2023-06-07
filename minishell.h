/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/07 17:10:38 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PRAMPT "mini🐢$>"
# define WHITE   "\x1b[1;37m"
# define YELLOW "\x1b[1;33m"
# define RED "\x1b[0;31m"
# define BLUE "\x1b[1;36m"
# define PINK "\x1b[1;35m"
# define GREEN "\x1b[1;32m"
# define RST_CLR "\x1b[0m"
# define INFILEE "<"
# define OUTFILEE ">"
# define APPENDD ">>"
# define HEREDOCC "<<"
# define PROMPT PINK"mi"YELLOW"ni"BLUE"hell🐢"RST_CLR"$>"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "./libft/libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stddef.h>
# include <signal.h>
# include <termios.h>

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
	int	here_doc_ret;
	int here_doc_aux;
	int	concurrency;
	int	free_expanded;
	int father;//for signals condition
}	t_flags;


typedef struct s_data
{
	char	separator[3];
	char	redirector[2];
	char	*input;
	char	*input_ex;
	char	*str_redic;
	char	**token1;
	char	**token2;
	char	**tokenized_cmd;
	char	**pipess;
	char	**commands;
	char	**infiles;//erase 
	char	**outfiles;//erase
	char	**redics;
	char	**env;
	int		**pipes;
	int		n_pipe;
	int		fd_in;
	int		fd_out; //for allredic3
	pid_t 	pid;
	int		fd_infile;
	int		fd_outfile;
	int		flag_env;//for export
	int		flag;
	t_flags	flags;
	pid_t	child_pid;
	int		child_status;
	int		original_std_out;
	int		original_std_in;
}	t_data;

typedef struct s_execute
	{
		char	**matriz_command;
		char	*str_path;
}	t_struc;

//BUILTS IN
int		ft_env(void);
int		ft_echo(char **arr);
int		ft_pwd(char **arr);
int		ft_exit(void);
int		ft_cd(char **arr);
int		ft_unset(char **arr);
int		ft_export(char **arr);
int		msg_error(char *s1, char *s2);
int		str_error(char *s1, char *s2);
int		str_error_export(char *s1, char *s2, char *s3);
int 	ft_get_var(char *str, int n);
char	**ft_abort(char **new_array, unsigned int i);
void	ft_copy(char **new_arr_env, char **arr, int i, int *n);
int		chdir_swap(char *new_path, char **arr);
char	*swap_arg(char *s1, char *s2);
void	gen_command_and_path(char **ar, char **en, char **path, char ***matriz);


//PIPEX
int 	ft_pipex(char **arr);
void	sent_to_pipe(char *str);
void	receive_from_send_to_pipe(char *str);
void	receive_from_pipe(char *str);

//INIT
int		init(void);

//LEXIC
int			ft_lexic(void);

//UTILS
int		ft_error(char *err);
int		ft_error_in(char *s1, char *s2, char *s3, int ret);
int		aux_del(int i);
int		delete_str(int i, int j, char *str);
int		ignore_redics(char *str, int *i);


//EXPAND
int		ft_check_expand(int i, int j, int flag_quote, int flag_expand);

//UNTOKEN
char	*ft_untoken(void);

//PROGRAM
int		ft_program(char *str);

//REDIC
char	get_next_redic(char *str, char c);

//ALLREDICS2
int		analyze_redicc(void);

//ALLREDIC
int		ft_redicc(char *str);

//ALLREDIC3
int		ft_open_outfile(int i);
int		ft_openn(int i);

//ALLUTILS
int		ft_de_oca_a_oca(int i, int j, int *flag_quote, int *flag_expand);
int		check_to_exe(void);
int		aux_dell(int i);

//WEDDING PLANNER
int		wedding_planner(void);

//SPECIAL SPLIT
char	**specialsplit(char *str, char c);

//SIGNALS
void 	set_signals(int n);
void 	sigint_handler(int sig);
void	sigint_handler_child(int sig);

//FREELANCER
int		freelancer(void);
int		ft_free_split(char **arr);
#endif
