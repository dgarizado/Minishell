/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/11 20:35:07 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define YELLOW "\x1b[1;33m"
# define RED "\x1b[0;31m"
# define BLUE "\x1b[1;36m"
# define PINK "\x1b[1;35m"
# define GREEN "\x1b[1;32m"
# define RST_CLR "\x1b[0m"

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

typedef struct s_flags
{
	int	token1;
	int	here_doc_ret;
	int	here_doc_aux;
	int	concurrency;
	int	free_expanded;
	int	wildcard_expanded;
	int	father;
}	t_flags;

typedef struct s_wildcard
{
	char	*start;
	char	*end;
	char 	*end_aux;
	int		type;
	
} t_wildcards;

typedef struct s_data
{
	char	*input;
	char	*input_ex;
	char	*str_redic;
	char	**token1;
	char	**tokenized_cmd;
	char	**commands;
	char	**infiles;
	char	**outfiles;
	char	**redics;
	char	**env;
	int		**pipes;
	int		n_pipe;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	pid_t	child_pid;
	t_flags	flags;
	t_wildcards	wc;
	int		child_status;
	int		original_std_out;
	int		original_std_in;
}	t_data;

//BUILTS IN
int				ft_env(void);
int				ft_echo(char **arr);
int				ft_pwd(char **arr);
int				ft_exit(void);
int				ft_cd(char **arr);
int				ft_unset(char **arr);
int				ft_export(char **arr);

//BUILT IN UTILS
int				ft_get_var(char *str, int n);
char			**ft_gen_new_arr(char *str_parsed);
char			**ft_abort(char **new_array, unsigned int i);
void			ft_copy(char **new_arr_env, char **arr, int i, int *n);
int				chdir_swap(char *new_path, char **arr);
char			*swap_arg(char *s1, char *s2);
void			gen_command_and_path(char **ar, char **en, \
char **path, char ***matriz);

//HANDLE_ERRORS
int				msg_error(char *s1, char *s2);
int				str_error(char *s1, char *s2);
int				str_error_export(char *s1, char *s2, char *s3);

//PIPEX
int				ft_pipex(char **arr);
void			sent_to_pipe(char *str);
void			receive_from_send_to_pipe(char *str);
void			receive_from_pipe(char *str);

//INIT
int				init(void);

//LEXIC
int				ft_lexic(void);

//UTILS
int				ft_error(char *err);
int				ft_error_in(char *s1, char *s2, char *s3, int ret);
int				aux_del(int i);
int				delete_str(int i, int j, char *str);
int				ignore_redics(char *str, int *i);
int				ft_alexic(void);

//EXPAND
int				ft_check_expand(int i, int j, int flag_quote, int flag_expand);

//UNTOKEN
char			*ft_untoken(void);
char			*ft_copyy(char *dest, const char *src, size_t index);

//PROGRAM
int				ft_program(char *str);

//REDIC
char			get_next_redic(char *str, char c);

//ALLREDICS2
int				analyze_redicc(void);

//ALLREDIC
int				ft_redicc(char *str);

//ALLREDIC3
int				ft_open_outfile(int i);
int				ft_openn(int i);

//ALLUTILS
int				ft_de_oca_a_oca(int i, int j, \
int *flag_quote, int *flag_expand);
int				check_to_exe(void);
int				aux_dell(int i);

//WEDDING PLANNER
int				wedding_planner(char *str);

//SPECIAL SPLIT
char			**specialsplit(char *str, char c);
unsigned char	*find_and_mark_chars(unsigned char *tmp);
int				count_str(char *str, char c);

//SIGNALS
void			set_signals(int n);
void			sigint_handler(int sig);
void			sigint_handler_child(int sig);

//FREELANCER
int				freelancer(void);
int				ft_free_split(char **arr);

//BONUS
char			**special_split_pipe(char *str);
char			**special_split_launcher(char *str, char *c);
int				ft_move_next_quotes(char *str, int i);
void			ft_move_next_quotes_pip(char *str, int *n, int *j);
int				ft_move_next_parenthesis(char *str, int i);
int				ft_prompt_and(char *arr);
int				ft_prompt_or(char *arr);
int				ft_check_to_and(char *arr);
int				ft_check_to_or(char *arr);
int				ft_prompt_launcher(char *arr);
int				status_and_free(char **prompts, int status);
int				ft_to_program(char **commands);
int				ft_check_paralel_parenthesis(char *str_trimed);


//BONUS WILDCARD
int				ft_check_wildcard(int i, int j, \
int flag_expand, int flag_quote);
int				ft_expand_star(int i, int j);
int				ft_replace_chr(char *str, char c, char r);
char			*ft_join_free(char *s1, char *s2);
char			*ft_more_stars(char *str);

#endif
