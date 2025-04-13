/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/13 17:01:34 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_simple_token(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '|' && input[*i] != '"' && input[*i] != '\''
		&& input[*i] != '<' && input[*i] != '>')
		(*i)++;
	if (*i == start)
		return (NULL);
	return (ft_substr(input, start, *i - start));
}

char	*get_next_token(char *input, int *i)
{
	char	*token;
	char	*quoted;

	token = NULL;
	quoted = NULL;
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (input[*i] == '|')
		return ((*i)++, ft_strdup("|"));
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quoted = handle_quotes(input, i, input[*i]);
		if (!quoted)
			return (NULL);
		return (quoted);
	}
	token = handle_special_tokens(input, i);
	if (token)
		return (token);
	return (get_simple_token(input, i));
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

void	single_fork(char **tokens, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_builtins(tokens, shell);
		exit(shell->exit_code);
	}
	else if (pid < 0)
	{
		perror("fork failed");
		shell->exit_code = 1;
	}
	else
	{
		waitpid(pid, &shell->exit_code, 0);
		shell->exit_code = WEXITSTATUS(shell->exit_code);
	}
}

void	execute_single_commands(char **tokens, t_shell *shell)
{
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
	{
		perror("Redirection failed!\n");
		dup_close(original_stdin, original_stdout);
		return ;
	}
	if (is_builtin(*tokens))
	{
		execute_custom_builtin(tokens, shell);
		dup_close(original_stdin, original_stdout);
		return ;
	}
	single_fork(tokens, shell);
	dup_close(original_stdin, original_stdout);
}
