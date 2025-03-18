/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <mmonika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:55:35 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/18 15:37:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	var_len(char *var)
// {
// 	size_t	i;

// 	i = 0;
// 	while (var[i] && var[i] != '=')
// 		i++;
// 	return (i);
// }

// char	*var_str(char *var)
// {
// 	size_t	i;

// 	i = var_len(var);
// 	if (!var[i])
// 		return (NULL);
// 	return (ft_strdup(var + i + 1));
// }

void	update_env(t_shell *minishell, char *var)
{
	t_dlist	*current;
	char	*str;
	size_t	i;
	
	current = minishell->denv;
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	while (current)
	{
		str = (char *)current->content;
		if (ft_strncmp(str, var, i) == 0 && (str[i] == '=' || str[i] == '\0'))
		{
			free (current->content);
			current->content = ft_strdup(var);
			return ;
		}
		current = current->next;
	}
	ft_dlstadd_back(&minishell->denv, ft_dlstnew(ft_strdup(var)));
}

int	ft_export(t_shell *minishell, char **custom_env)
{
	int	i;
	t_dlist	*current;

	i = 1;
	current = minishell->denv;
	if (!custom_env[1])
	{
		while (current)
		{
			printf("declare -x %s\n", (char *)current->content);
        	current = current->next;
		}
		return (SUCCESS);
	}
	while (custom_env[i])
	{
		if (!is_valid_var(custom_env[i]))
		{
			ft_putstr_fd("export: ", STDERR_FILENO);
			ft_putstr_fd(custom_env[i], STDERR_FILENO);
			ft_putstr_fd(" is invalid\n", STDERR_FILENO);
			minishell->exit_code = 1;
		}
		else
			update_env(minishell, custom_env[i]);
		i++;
	}
	return (SUCCESS);
}

int	ft_env(t_shell *minishell)
{
	t_dlist	*current;

	current = minishell->denv;
	while (current)
	{
		printf("%s\n", (char *)current->content);
    	current = current->next;
	}
	return (SUCCESS);
}
