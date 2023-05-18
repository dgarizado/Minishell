/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:55:30 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/18 22:32:19 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trimed;
	size_t	len;

	len = ft_strlen(s1);
	while (s1[0] != '\0' && ft_strchr(set, s1[0]))
		s1++;
	len = ft_strlen(s1);
	while (s1[0] != '\0' && ft_strrchr(set, s1[len - 1]))
		len--;
	str_trimed = ft_substr(s1, 0, len);
	return (str_trimed);
}

static char	*copy(char *str_program, char *str_path, char *program)
{
	size_t	j;

	j = 0;
	while (str_path[j++] != '\0')
	str_program = (char *)calloc(j + ft_strlen(program) + 2, sizeof(char));
	if (!(str_program))
		return (NULL);
	j = ft_strlcpy(str_program, str_path, j + 1);
	str_program[j++] = '/';
	j = j + ft_strlcpy(&str_program[j], program, ft_strlen(program) + 1);
	str_program[j] = '\0';
	return (str_program);
}

static char	*matriz_cat_program(char**matriz_path, char*program)
{
	size_t	i;
	char	*str_program;

	i = 0;
	while (matriz_path[i] != NULL)
	{
		str_program = copy(str_program, matriz_path[i], program);
		if (!access(str_program, 0))
		{
			ft_abort(matriz_path, ft_arrlen(matriz_path));
			return (str_program);
		}
		free(str_program);
		i++;
	}
	ft_abort(matriz_path, ft_arrlen(matriz_path));
	return (NULL);
}

static char	*gen_str_path(char**env, char *path, char *name)
{
	size_t	i;
	char	**matriz_path;
	char	*program;

	program = name;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], path, ft_strlen(path)) == 0)
			break ;
		i++;
	}
	if (!env[i])
	{
		str_error("env", "not avaible");
		exit(errno);
	}
	matriz_path = ft_split(&env[i][ft_strlen(program) + 1], ':');
	return (matriz_cat_program(matriz_path, program));
}

void	gen_command_and_path(char **ar, char **en, char **path, char ***matriz)
{
		*matriz = ar;
		*path = gen_str_path(en, "PATH", ar[0]);
}
