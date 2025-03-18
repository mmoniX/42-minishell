/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <mmonika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:29:57 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/18 15:43:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int is_valid_var(char *var)
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
	else if (!ft_strcmp(args, "pwd"))
		return (1);
	else if (!ft_strcmp(args, "unset"))
		return (1);
	else if (!ft_strcmp(args, "export"))
		return (1);
	else if (!ft_strcmp(args, "env"))
		return (1);
	return (0);
}

int	execute_builtin(char **tokens, t_shell *minishell)
{
	if (!ft_strcmp(tokens[0], "echo"))
		return (ft_echo(tokens));
	if (!ft_strcmp(tokens[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(tokens[0], "unset"))
		return (ft_unset(minishell, tokens));
	if (!ft_strcmp(tokens[0], "export"))
		return (ft_export(minishell, tokens));
	if (!ft_strcmp(tokens[0], "env"))
		return (ft_env(minishell));
	return (1);
}
