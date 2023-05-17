/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:05:51 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/17 21:31:25 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_error(char *s1, char *s2)
{
	write(2, s1, ft_strlen(s1));
	write(2, ": ", 2);
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
	return (errno);
}

int str_error_export(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	write(2, ": ", 2);
	write(2, s2, ft_strlen(s2));
	write(2, " ", 1);
	write(2, s3, ft_strlen(s3));
	write(2, "\n", 1);
	return (errno);
}

int	msg_error(char *s1, char *s2)
{
	write(2, s1, ft_strlen(s1));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
	return (errno);
}
