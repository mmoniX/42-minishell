/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/06 16:11:57 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_next_token(char *input, int *i)
{
	int		start;
	char	*token;

	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (input[*i] == '|')
	{
		(*i)++;
		token = ft_strdup("|");
		if (!token)
			return (NULL);
		return (token);
	}
	else if (input[*i] == '"' || input[*i] == '\'')
		return (handle_quotes(input, i, input[*i]));
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	token = ft_substr(input, start, *i - start);
	if (!token)
		return (NULL);
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
		return (perror("No command to execute.\n"));
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
		execute_builtins(tokens, shell);
	waitpid(pid, &shell->exit_code, 0);
	shell->exit_code = WEXITSTATUS(shell->exit_code);
	dup_close(original_stdin, original_stdout);
}

void	process_input(t_shell *shell, char *input)
{
	char	**tokens;
	char	**commands;
	char	*final_input;

	final_input = expand_variables(input, shell);
	if (!final_input || !*final_input)
		return ;
	if (ft_strchr(final_input, '|'))
	{
		commands = split_pipes(final_input);
		if (commands)
		{
			execute_piped_commands(commands, shell);
			ft_free_tab(commands);
		}
	}
	else
	{
		tokens = tokenize_input(final_input, shell);
		if (tokens && tokens[0])
			execute_single_commands(tokens, shell);
		ft_free_tab(tokens);
	}
	free(final_input);
}
