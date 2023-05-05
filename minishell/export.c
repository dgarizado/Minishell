/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:35:38 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/05 01:07:07 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void check(void)
{
	system("leaks a.out");
}

void printf_argv(char **new_arg)
{
	int n;

	n = 0;
	while(new_arg[n])
	{
		printf("%s\n", new_arg[n]);
		n++;
	}
}

static char	**ft_abort(char **new_array, unsigned int i)
{
	while (i-- > 0)
		free(new_array[i]);
	free(new_array);
	return (0);
}

int	ft_arrlen(char **env)
{
	int n;

	n = 0;
	while (env[n])
		n++;
	return(n);
}

int	ft_gen_new_env(char **arr, char **new_env, int len_env)
{
	int i;
	int n;

	i = 0;
	n = 0;
	len_env = ft_arrlen(environ);
	printf("len_env%d\n", len_env);
	new_env = (char **)malloc(sizeof(char *) * len_env + ft_arrlen(arr) -1);
	while(i < len_env)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	printf(" i %d\n", i);
	while (i < len_env + ft_arrlen(arr)-1)
	{
		new_env[i] = ft_strdup(arr[n]);
		n++;
		i++;
	}
	printf(" n %d\n", n);
	printf(" i %d\n", i);
	new_env[i] = NULL;
	return (0);
}


int ft_export(char **arr)
{
	char **new_env;
	int i;
	int len_env;
	i = 0;

	if (!environ)
	{
		str_error("export", "env not found");
		return(EXIT_SUCCESS);
	}
	if (!arr[1])
	{
		printf_argv(environ);
		return ( 0);
	}
	ft_gen_new_env(arr, new_env, len_env);
	environ = new_env;
	return ( 0);
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


int main(int argc, char **argv, char **env)// 0 a.out 1 hola 2NULL
{

	swap_argv(argc, argv);
	ft_export(argv);
	//printf_argv(environ);
	
	//ft_abort(argv, len_env);
	//atexit(check);*/
	printf("**************%s\n", getenv("AL"));
	//ft_abort(argv, ft_arrlen(environ) );
	//atexit(check);
	return (0);
	

}