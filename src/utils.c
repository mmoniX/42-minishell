/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:14:30 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/17 13:35:24 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*temp;

	temp = malloc(sizeof(t_dlist));
	if (!temp)
		return (NULL);
	temp->content = content;
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}
