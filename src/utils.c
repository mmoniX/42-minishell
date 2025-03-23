/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:14:30 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/23 14:01:25 by gahmed           ###   ########.fr       */
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
	temp = ft_dlstnew(env[0]);
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

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_execvp(char *cmd, char **args, char **env)
{
	char *full_path;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return execve(cmd, args, env);
	full_path = get_path(cmd, env);
	if (!full_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		return -1;
	}
	if (execve(full_path, args, env) == -1)
	{
		perror("execve failed");
		free(full_path);
		return -1;
	}
	free(full_path);
	return 0;
}
