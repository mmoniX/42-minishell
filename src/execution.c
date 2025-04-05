/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/05 13:40:06 by mmonika          ###   ########.fr       */
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

// int	count_tokens(char *input)
// {
// 	char	*token;
// 	int		count;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	count = 0;
// 	while (input[i])
// 	{
// 		j = i;
// 		token = get_next_token(input, &i);
// 		if (token)
// 		{
// 			count++;
// 			free (token);
// 		}
// 		else if (i == j)
// 			break ;
// 		else if (!token)
// 			return (FAIL);
// 	}
// 	return (count);
// }

char	**tokenize_input(char *input)
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
	return (tokens);
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
	pid = fork();
	if (pid == 0)
		execute_builtins(tokens, shell);
	else if (pid < 0)
	{
		shell->exit_code = 1;
		return (perror("fork failed"));
	}
	waitpid(pid, &shell->exit_code, 0);
	shell->exit_code = WEXITSTATUS(shell->exit_code);
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
		tokens = tokenize_input(final_input);
		if (tokens && tokens[0])
			execute_single_commands(tokens, shell);
		ft_free_tab(tokens);
	}
	free(final_input);
}
