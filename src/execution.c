/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/24 14:55:40 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	*index = end + 1;
	return (quoted_str);
}

char	**tokenize_input(char *input)
{
	char	**tokens;
	char	*quoted_str;
	int		start;
	int		i;
	int		j;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (perror("malloc failed for tokens"), NULL);
	i = 0;
	j = 0;
	while (input[i] && j < MAX_TOKENS - 1)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			tokens[j++] = ft_strdup("|");
			i++;
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			quoted_str = handle_quotes(input, &i, input[i]);
			if (!quoted_str)
				return (free(tokens), NULL);
			tokens[j++] = quoted_str;
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' '
				&& input[i] != '|' && input[i] != '"' && input[i] != '\'')
				i++;
			tokens[j] = ft_strndup (&input[start], i - start);
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

void	execute_command(char **tokens, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		original_stdin = dup(STDIN_FILENO);
	int		original_stdout = dup(STDOUT_FILENO);

	if (!tokens || !tokens[0])
	{
		printf("No command to execute.\n");
		return ;
	}
	if (handle_redirections(tokens) < 0)
	{
		printf("Redirection failed!\n");
        return;
	}
	if (is_builtin(tokens[0]))
	{
		execute_builtin(tokens, shell);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		execute_redirection(tokens, shell);
		exit(shell->exit_code);
		ft_execvp(tokens[0], tokens, shell->env);
		perror("execvp failed");
		exit(127);
	}
	else if (pid < 0)
	{
		perror("fork failed");
		shell->exit_code = 1;
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

void	process_input(t_shell *shell, char *input)
{
	char	**tokens;
	char	**commands;
	char	*final_input;

	final_input = expand_variables(input, shell);
	if (!final_input || !*final_input)
		return (free(input));
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
		tokens = tokenize_input(final_input);
		if (tokens && tokens[0])
			execute_command(tokens, shell);
		ft_free_tab(tokens);
	}
	free(final_input);
	free(input);
}
