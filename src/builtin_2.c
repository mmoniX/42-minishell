/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:55:35 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/25 13:32:53 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	i = 1;
	if (!custom_env[1])
	{
		ft_env(minishell, 1);
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
			return (FAIL);
		}
		else
			update_env(minishell, custom_env[i]);
		i++;
	}
	return (SUCCESS);
}

void	update_directory(t_shell *minishell)
{
	char	*new_pwd;
	t_dlist	*current;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("cd: getcwd error"));
	if (minishell->old_pwd)
		free (minishell->old_pwd);
	minishell->old_pwd = ft_strdup(new_pwd);
	current = minishell->denv;
	while (current)
	{
		if (ft_strncmp(current->content, "PWD=", 4) == 0)
		{
			free(current->content);
			current->content = ft_strjoin("PWD=", new_pwd);
			break ;
		}
		current = current->next;
	}
	free(new_pwd);
}

int	ft_cd(t_shell *minishell, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			minishell->exit_code = 1;
			return (FAIL);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		minishell->exit_code = 1;
		return (FAIL);
	}
	update_directory(minishell);
	return (SUCCESS);
}

int	ft_exit(t_shell *minishell, char *args)
{
	printf("exit\n");
	free(args);
	if (minishell->old_pwd)
		free(minishell->old_pwd);
	if (minishell->denv)
		ft_free_dlist(minishell->denv);
	return (minishell->exit_code);
}
