/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:54:02 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/23 19:46:58 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

int	ft_printf_arr(char **arr)
{
	int	n;

	n = 0;
	if (!arr)
		return (msg_error(arr[0], "env"));
	while (arr[n])
	{
		printf("%s\n", arr[n]);
		n++;
	}
	return (EXIT_SUCCESS);
}
