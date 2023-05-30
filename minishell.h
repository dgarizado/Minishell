/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/29 21:15:45 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PRAMPT "mini🐢$>"
# define WHITE   "\x1b[1;37m"
# define YELLOW "\x1b[1;33m"
#define RED "\x1b[0;31m"
# define BLUE "\x1b[1;36m"
# define PINK "\x1b[1;35m"
# define RST_CLR "\x1b[0m"
# define INFILEE "<"
# define OUTFILEE ">"
# define APPENDD ">>"
# define HEREDOCC "<<"
# define OK 0
# define PARSE g_data.flag
# define EXE_IN_SUBPROCESS g_data.flag
# define EXE_IN_PROCESS check_to_exe()
# define STATUS g_data.flag
# define YES -1
# define INPUT g_data.input



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
	char	**pipess;
	char	**commands;
	char	**infiles;//erase 
	char	**outfiles;//erase
	char	**redics;
	char	**env;
	int		**pipes;
	int		tmp_n_pipes;
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
}	t_data;

typedef struct s_execute
	{
		char	**matriz_command;
		char	*str_path;
}	t_struc;

//MAIN
int		init_prompt_subps(void);

//BUILTS IN
int		ft_pwd(char **arr);
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
int		ft_unset(char **arr);
void	ft_copy(char **new_arr_env, char **arr, int i, int *n);
int 	ft_get_var(char *str, int n);
int		ft_echo(char **arr);
void	gen_command_and_path(char **ar, char **en, char **path, char ***matriz);
char	**pipexsplit(char *str);
int		ft_env(void);
int		str_error_export(char *s1, char *s2, char *s3);


//PIPEX
int 	ft_pipex(char **arr);
void	sent_to_pipe(char *str);
void	receive_from_send_to_pipe(char *str);
void	receive_from_pipe(char *str);
void	close_all_pipes(void);

//INIT
int		init(void);

//LEXIC
int			ft_lexic(void);
bool		is_enclosed(const char *str, int idx);
int			ft_is_closed(char *str, int *index, char c);
int			ft_check_pipes(void);
int			ft_check_exe(void);

//PIPEX SPLIT
char	**pipexsplit(char *str);

//UTILS
int		ft_error(char *err);
int		delete_str(int i, int j, char *str);
int		aux_del(int i);

//EXPAND
int		ft_check_expand(void);

//UNTOKEN
char	*ft_untoken(void);
char	*ft_join(char *s1, char *s2);

//PROGRAM
int		ft_program(char *str);

//REDIC
// int		ft_redic(char *str);
char	get_next_redic(char *str, char c);

// //REDIC2
// int		analyze_redic(void);
int		ft_error_in(char *s1, char *s2, char *s3, int ret);
int		delimiterr(char *eof, int *fd, int std_out);

// //REDIC3
// int		ft_open(int i);
// int		check_here_docs(void);

//ALLREDIC
int		ft_redicc(char *str);

//ALLREDIC23
int		analyze_redicc(void);
int		ft_openn(int i);
int		ft_open_outfile(int i);

//ALLUTILS
int		aux_dell(int i);

//WEDDING PLANNER
int		wedding_planner(void);

//EXECUTE
int		ft_execute(char **arr);

//SPECIAL SPLIT
char	**specialsplit(char *str, char c);

//SIGNALS
void 	set_signals(int n);
void 	sigint_handler(int sig);
void sigint_handler_child(int sig);
#endif
