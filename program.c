/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:59:17 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/17 18:57:26 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

// int	ft_redic(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*redirector;
// 	char	*red;
	
// 	i = 0;
// 	while (i < REDIR_COUNT)
// 	{
// 		redirector = ft_strchr(str, g_data.redirector[i]);
// 		if (redirector != NULL)
// 		{
// 			j = i;
// 			while (redirector[j] != '\0' && redirector[j] != ' ' && redirector[j] != '<' && redirector[j] != '>')
// 			{
// 				j++;
// 			}
// 			red = ft_substr(redirector, 0, j);
// 			printf("\nFOUND:'%s'\n", redirector);
// 			printf("\nreFOUND:'%s'\n", red);	
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	ft_count_redic(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (str[0] == c)
		{
			count++;
			if (str[1] == c)
				str++;
		}
		str++;
	}
	return (count);
}

char	get_next_redic(char *str, char c)
{
	int		i;
	int		count;
	int		j;
	int		k;
	char	*aux;

	i = 0;
	k = 0;
	aux = ft_substr(str, 0, ft_strlen(str) + 1);
	printf("\ncopied:%s\n", str);
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			j = i + 1;
			while (str[j] == ' ')
				j++;
			while(str[j] != '\0' && str[j] != ' ')	
			{
				count++;
				j++;
				if (str[j] == '\0' || str[j] == ' ')
				{
					g_data.infiles[k] = ft_substr(aux, i, j);
					printf("\nredic: %s\n", g_data.infiles[k]);
					k++;
					
				}
			}	
		}
		i++;
	}
	return (count);
}

/**
 * @brief Reveives a unique string containin only one command and
 * their redirections. 
 * Checks if there are redirections and removes them from
 * the arguments.
 * Performs the redirections.
 * @param str 
 * @return int 
 */
int	ft_program(char *str)
{
	// // while (str)
	// // {
	// 	ft_redic(str);
	// 	str++;
	// // }
	//GET NEXT REDIC
	int i = 0;
	i = ft_count_redic(str, '>');
	g_data.outfiles = ft_calloc(sizeof(char *), i + 1);
	i = ft_count_redic(str, '<');
	g_data.infiles = ft_calloc(sizeof(char *), i + 1);
	printf("\ncame in: %s infiles\n", str);
	printf("\nfirst redic has: %d characters\n", get_next_redic(str, '<'));
	return (0);
}
