/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:44:08 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/13 17:02:26 by mmonika          ###   ########.fr       */
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
				return (ft_putstr_fd("Syntax Error\n", STDERR_FILENO), FAIL);
		}
		if (is_redirection(args[i]))
		{
			if (!args[i + 1] || is_redirection(args[i + 1])
				|| !ft_strcmp(args[i + 1], "|"))
				return (ft_putstr_fd("Syntax Error\n", STDERR_FILENO), FAIL);
		}
	}
	return (SUCCESS);
}

char	*handle_quotes(const char *input, int *index, char quote_type)
{
	int		start;
	int		end;
	char	*quoted_str;

	start = *index + 1;
	end = start;
	while (input[end] && input[end] != quote_type)
		end++;
	if (input[end] != quote_type)
	{
		ft_putstr_fd("Error: Unclosed quote\n", STDERR_FILENO);
		return (NULL);
	}
	quoted_str = ft_strndup(&input[start], end - start);
	if (!quoted_str)
		return (NULL);
	*index = end + 1;
	return (quoted_str);
}

char	*handle_special_tokens(char *input, int *i)
{
	char	*token;

	if (input[*i] == '>' || input[*i] == '<')
	{
		if ((input[*i] == '>' && input[*i + 1] == '>')
			|| (input[*i] == '<' && input[*i + 1] == '<'))
		{
			token = ft_substr(input, *i, 2);
			*i += 2;
		}
		else
		{
			token = ft_substr(input, *i, 1);
			(*i)++;
		}
		return (token);
	}
	return (NULL);
}
