/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:44:08 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/13 10:11:52 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redirection(char *token)
{
	return (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, "<<"));
}

int	is_valid_token(char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, "<<") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "|"))
		return (1);
	if (ft_strlen(token) > 2 && (token[0] == '<' || token[0] == '>'))
		return (0);
	return (1);
}

int	check_syntax_errors(char **args)
{
	int	i;

	if (!args || !args[0])
		return (SUCCESS);
	i = -1;
	while (args[++i])
	{
		if (!is_valid_token(args[i]))
			return (ft_putstr_fd("Syntax Error\n", STDERR_FILENO), FAIL);
		if (!ft_strcmp(args[i], "|"))
		{
			if (i == 0 || !args[i + 1] || !ft_strcmp(args[i + 1], "|"))
				return (ft_putstr_fd("Syntax Error: invalid pipe\n", STDERR_FILENO), FAIL);
		}
		if (is_redirection(args[i]))
		{
			if (!args[i + 1] || is_redirection(args[i + 1]) || !ft_strcmp(args[i + 1], "|"))
				return (ft_putstr_fd("Syntax Error: invalid redirection\n", STDERR_FILENO), FAIL);
		}
	}
	return (SUCCESS);
}

int	is_pipe(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
	return (c == '|' && *quote == 0);
}
