/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:57:57 by dgarizad          #+#    #+#             */
/*   Updated: 2022/12/01 17:10:09 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_compare(unsigned char s1, unsigned char s2)
{
	int	result;

	result = s1 - s2;
	return (result);
}

int	ft_strncmp(const char *s1, const char*s2, unsigned int n)
{
	unsigned int	i;
	int				result;

	i = 0;
	result = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
		{
			result = ft_compare(s1[i], s2[i]);
			break ;
		}
		i++;
	}
	return (result);
}
