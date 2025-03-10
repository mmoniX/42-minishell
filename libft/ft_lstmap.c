/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:02:42 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/10 15:04:20 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*obj;

	if (lst && f && del)
	{
		temp = ft_lstnew(f(lst->content));
		obj = temp;
		while (lst->next)
		{
			lst = lst->next;
			obj->next = ft_lstnew(f(lst->content));
			if (lst->content == NULL)
				ft_lstdelone(temp, del);
			obj = obj->next;
		}
		return (temp);
	}
	return (NULL);
}
