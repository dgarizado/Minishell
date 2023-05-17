/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:40:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/17 21:16:57 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	size_t	ft_cmp(const char *s1, const char*s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s2[i] != 0 && i < n)
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_strstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (*needle == haystack[i])
		{
			if (ft_cmp(&haystack[i], needle, len - i) == 1 \
			&& (ft_strlen(needle) <= len - i))
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

static char	*gen_new_path(char *path, char *arg1, char *arg2, int n_bytes)
{
	char	*before_path;
	char	*after_path;
	char	*str_cat_s1;
	char	*new_path;
	int		n_bytes_arg1;

	str_cat_s1 = ft_substr(path, 0, n_bytes);
	before_path = ft_strjoin(str_cat_s1, arg2);
	n_bytes_arg1 = ft_strlen(arg1);
	after_path = ft_substr(path, n_bytes + n_bytes_arg1, ft_strlen(path) \
	- (n_bytes + n_bytes_arg1));
	new_path = ft_strjoin(before_path, after_path);
	free(before_path);
	free(after_path);
	free(str_cat_s1);
	return (new_path);
}

char	*swap_arg(char *s1, char *s2)
{
	char	vector[256];
	int		n_bytes;

	getcwd(vector, sizeof(vector));
	n_bytes = ft_strstr(vector, s1, ft_strlen(vector));
	if (n_bytes != -1)
		return (gen_new_path(vector, s1, s2, n_bytes));
	else
	{
		str_error("cd: string not in pwd", s1);
		return (NULL);
	}
}

int	chdir_swap(char *new_path, char **arr)
{
	int	status;

	if (!new_path)
		return (errno);
	status = chdir(new_path);
	if (!status)
	{
		free(new_path);
		return (0);
	}
	else
	{
		msg_error(arr[0], new_path);
		free(new_path);
		return (errno);
	}
}
