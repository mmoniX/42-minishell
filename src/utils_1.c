/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:14:30 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/13 16:48:16 by mmonika          ###   ########.fr       */
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

t_dlist	*convert_env_to_list(char **env)
{
	t_dlist	*temp;
	t_dlist	*current;
	int		i;

	if (!env || !*env)
		return (NULL);
	temp = ft_dlstnew(ft_strdup(env[0]));
	current = temp;
	i = 1;
	while (env[i])
	{
		current->next = ft_dlstnew(ft_strdup(env[i]));
		current->next->prev = current;
		current = current->next;
		i++;
	}
	return (temp);
}

char	*ms_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc (len * sizeof(char));
	if (!str)
		return (free (s1), NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	free(s1);
	free(s2);
	return (str);
}

int	skip_empty_token(char **token)
{
	if (!token || !token[0])
	{
		ft_free_tab(token);
		return (FAIL);
	}
	return (SUCCESS);
}
