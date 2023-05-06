/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:39:50 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/06 02:55:20 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void check(void)
{
	system("leaks a.out");
}

static int	ft_arrlen(char **env)
{
	int	n;

	n = 0;
	while (env[n])
		n++;
	return (n);
}

char	**ft_abort(char **new_array, unsigned int i)
{
	while (i-- > 0)
		free(new_array[i]);
	free(new_array);
	return (0);
}

void	ft_printf_arr(char **new_arg)
{
	int	n;

	n = 0;
	while (new_arg[n])
	{
		printf("%s\n", new_arg[n]);
		n++;
	}
}

static char	**ft_gen_new_env(char **arr)
{
	char **new_env;
	int	len_env;
	int	i;
	int	n;

	i = 0;
	n = 1;
	len_env = ft_arrlen(environ);
	new_env = (char **)malloc(sizeof(char *) * (len_env + 1 + \
	ft_arrlen(arr -1)));
	while (i < len_env)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	while (i < len_env + ft_arrlen(arr)-1)
		new_env[i++] = ft_strdup(arr[n++]);
	new_env[i] = NULL;
	return (new_env);
}

char **ft_export_set(char **arr, char ***static_env)
{
	char **new_env;
	
	if (!environ)
	{
		str_error("export", "env not found");
		return(NULL);
	}
	if (!arr[1])
	{
		ft_printf_arr(environ);
		return (EXIT_SUCCESS);
	}
	new_env = ft_gen_new_env(arr);
	if (!(*static_env))
		*static_env = new_env;
	else
	{
		ft_abort(*static_env, ft_arrlen(*static_env));
		*static_env = new_env;
	}
	return (new_env);
}


int	ft_export(char **arr, char *str)
{
	static char		**static_env;

	if (!ft_strncmp(str, "set", 3))
		environ = ft_export_set(arr, &static_env);
	if(!ft_strncmp(str, "unset", 5))
		environ = ft_export_unset(arr, &static_env);
	return (errno);
}

void	swap_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	if(!argv)
		return;
	while (i < argc -1)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[argc - 1] = NULL;
}
/*
int main(int argc, char **argv)
{
	int n = 0;

	swap_argv(argc, argv);
	//ft_printf_arr(environ);
	write(1, "----------------------------------------\n", 42);
	while (n < 1)
	{
		ft_export(argv, "set");
		ft_export(argv, "unset");
		n++;
	}
	write(1, "----------------------------------------\n", 42);
	ft_printf_arr(environ);
	write(1, "----------------------------------------\n", 42);
	atexit(check);
	return (0);
}
*/