/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:25:37 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/20 20:51:13 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief writes the string 
 * into the file descriptor with a newline.
 * @param s 
 * @param fd 
 */
void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (*(s + i))
		write(fd, (s + i++), 1);
	write(fd, "\n", 1);
}
