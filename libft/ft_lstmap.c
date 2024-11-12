/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:04:34 by jco               #+#    #+#             */
/*   Updated: 2023/11/29 16:08:20 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;
	t_list	*new_node;
	void	*content_result;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	current = NULL;
	while (lst)
	{
		content_result = f(lst->content);
		new_node = ft_lstnew(content_result);
		if (!content_result || !new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		if (!new_list)
		{
			new_list = new_node;
			current = new_node;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		lst = lst->next;
	}
	return (new_list);
}*/

static t_list	*create_node(void *content_result)
{
	t_list	*new_node;

	new_node = ft_lstnew(content_result);
	if (!new_node)
		return (NULL);
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;
	void	*content_result;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	current = NULL;
	while (lst)
	{
		content_result = f(lst->content);
		current = create_node(content_result);
		if (!current)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, current);
		lst = lst->next;
	}
	return (new_list);
}
