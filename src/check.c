/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:44:08 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/05 18:17:50 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_syntax_errors(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if ((ft_strcmp(args[i], "<>") == 0) || (ft_strcmp(args[i], "><") == 0)
			|| (ft_strcmp(args[i], ">>>") == 0) || (ft_strcmp(args[i],
					"<<<") == 0))
			return (ft_putstr_fd("Syntax Error\n", STDERR_FILENO), FAIL);
		if ((ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0
				|| ft_strcmp(args[i], ">>") == 0) && (!args[i + 1] || (args[i
						+ 1] && ft_strlen(args[i + 1]) == 0)))
			return (ft_putstr_fd("Syntax Error\n", STDERR_FILENO), FAIL);
		if ((ft_strcmp(args[i], "<<") == 0) && (!args[i + 1] || (args[i + 1]
					&& ft_strlen(args[i + 1]) == 0)))
			return (ft_putstr_fd("Syntax Error\n", STDERR_FILENO), FAIL);
	}
	return (SUCCESS);
}

int	check_quote(char *input, int value_i)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	while (++i < value_i)
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote != 0 && quote == input[i])
			quote = 0;
	}
	return ((int)quote);
}

int	check_pipe(char *input, int i)
{
	if (input[i] == '|' && !check_quote(input, i) && input[i + 1]
		&& input[i + 1] == '|')
		return (ft_putstr_fd("Syntax Error: `||\'\n", STDERR_FILENO), FAIL);
	else if (input[0] == '|' && !check_quote(input, i))
		return (ft_putstr_fd("Syntax Error:  `|\'\n", STDERR_FILENO), FAIL);
	return (SUCCESS);
}

int	check_input(t_shell *shell, char *input)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while (input[++i])
	{
		if (check_pipe(input, i))
		{
			shell->exit_code = 2;
			return (free(input), FAIL);
		}
		if (pipe != 1 && input[i] == '|' && !check_quote(input, i))
			pipe = 1;
		else if (ft_isprint(input[i]) && input[i] != ' ' && input[i] != '|')
			pipe = 0;
		else if (input[i] == '|')
			break ;
	}
	if (pipe == 1)
		return (ft_putstr_fd("Syntax Error: `|\'\n", STDERR_FILENO),
			shell->exit_code = 2, FAIL);
	return (SUCCESS);
}
