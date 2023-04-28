/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:06:25 by dgarizad          #+#    #+#             */
/*   Updated: 2022/12/09 16:07:01 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;

	new_list = 0;
	while (lst)
	{
		new_node = malloc(sizeof(t_list));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node -> content = f(lst -> content);
		new_node -> next = NULL;
		ft_lstadd_back(&new_list, new_node);
		lst = lst -> next;
	}
	return (new_list);
}
