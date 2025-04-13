/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:38:05 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/13 16:42:03 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_dlist(t_dlist *env)
{
	t_dlist	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_token(char **token)
{
	if (*token)
	{
		free(*token);
		*token = NULL;
	}
}

void	dup_close(int o_stdin, int o_stdout)
{
	dup2(o_stdin, STDIN_FILENO);
	dup2(o_stdout, STDOUT_FILENO);
	close(o_stdin);
	close(o_stdout);
}

char	*malloc_protection(char *str)
{
	if (!str)
	{
		perror("Malloc Failed");
		return (NULL);
	}
	return (str);
}
