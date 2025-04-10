/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/10 12:17:55 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*handle_special_tokens(char *input, int *i)
{
	char	*token;

	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		if ((input[*i] == '<' && input[*i + 1] == '<')
			|| (input[*i] == '>' && input[*i + 1] == '>'))
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
	else if (input[*i] == '"' || input[*i] == '\'')
		return (handle_quotes(input, i, input[*i]));
	return (NULL);
}

char	*get_next_token(char *input, int *i)
{
	int		start;
	char	*token;

	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (!input[*i])
		return (NULL);
	token = handle_special_tokens(input, i);
	if (token)
		return (token);
	start = *i;
	while (input[*i] && !(input[*i] == ' ' || input[*i] == '\t'
			|| input[*i] == '|' || input[*i] == '<' || input[*i] == '>'
			|| input[*i] == '"' || input[*i] == '\''))
	{
		if ((input[*i] == '<' || input[*i] == '>') && (*i != start))
			break ;
		(*i)++;
	}
	token = ft_substr(input, start, *i - start);
	return (token);
}

char	**tokenize_input(char *input, t_shell *shell)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = malloc(sizeof(char *) * MAX_TOKEN);
	if (!tokens)
		return (perror("malloc failed for tokens"), NULL);
	i = 0;
	j = 0;
	while (input[i] && j < MAX_TOKEN - 1)
	{
		tokens[j] = get_next_token(input, &i);
		if (!tokens[j])
			break ;
		j++;
	}
	tokens[j] = NULL;
	if (check_syntax_errors(tokens) == FAIL)
		return (ft_free_tab(tokens), shell->exit_code = 258, NULL);
	else
		return (tokens);
}

void	dup_close(int o_stdin, int o_stdout)
{
	dup2(o_stdin, STDIN_FILENO);
	dup2(o_stdout, STDOUT_FILENO);
	close(o_stdin);
	close(o_stdout);
}

void	execute_single_commands(char **tokens, t_shell *shell)
{
	pid_t	pid;
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (!tokens || !tokens[0])
	{
		dup_close(original_stdin, original_stdout);
		shell->exit_code = 0;
		return ;
	}
	if (handle_redirections(tokens, shell) < 0)
		return (perror("Redirection failed!\n"));
	if (is_builtin(*tokens))
	{
		execute_custom_builtin(tokens, shell);
		dup_close(original_stdin, original_stdout);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execute_builtins(tokens, shell);
		exit(shell->exit_code);
	}
	waitpid(pid, &shell->exit_code, 0);
	shell->exit_code = WEXITSTATUS(shell->exit_code);
	dup_close(original_stdin, original_stdout);
}
