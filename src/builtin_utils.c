/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:29:57 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/04 17:31:59 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_var(char *var)
{
	int	i;

	if (!var || !var[0] || ft_isdigit(var[0]))
		return (0);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	if (var[i] == '=' && i == 0)
		return (0);
	return (1);
}

int	is_builtin(char *args)
{
	if (!args)
		return (0);
	else if (!ft_strcmp(args, "echo"))
		return (1);
	else if (!ft_strcmp(args, "cd"))
		return (1);
	else if (!ft_strcmp(args, "pwd"))
		return (1);
	else if (!ft_strcmp(args, "export"))
		return (1);
	else if (!ft_strcmp(args, "unset"))
		return (1);
	else if (!ft_strcmp(args, "env"))
		return (1);
	return (0);
}

int	execute_custom_builtin(char **tokens, t_shell *minishell)
{
	if (!ft_strcmp(tokens[0], "echo"))
		return (ft_echo(tokens));
	if (!ft_strcmp(tokens[0], "cd"))
		return (ft_cd(minishell, tokens));
	if (!ft_strcmp(tokens[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(tokens[0], "export"))
		return (ft_export(minishell, tokens));
	if (!ft_strcmp(tokens[0], "unset"))
		return (ft_unset(minishell, tokens));
	if (!ft_strcmp(tokens[0], "env"))
		return (ft_env(minishell, 0));
	return (1);
}

void	execute_builtins(char **tokens, t_shell *shell)
{
	if (is_builtin(tokens[0]))
		execute_custom_builtin(tokens, shell);
	else
	{
		ft_execvp(tokens[0], tokens, shell->env);
		perror("execvp failed");
		shell->exit_code = 127;
	}
	exit(shell->exit_code);
}
