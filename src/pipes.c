/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/13 16:08:03 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**split_pipes(char *input)
{
	char	**commands;
	int		i;
	int		start;
	int		end;
	char	quote;

	i = 0;
	start = 0;
	end = 0;
	quote = 0;
	commands = malloc(sizeof(char *) * (count_pipes(input) + 2));
	if (!commands)
		return (perror("pipe malloc failed"), NULL);
	while (input[end])
	{
		if (is_pipe(input[end], &quote))
		{
			commands[i++] = ft_strndup(&input[start], end - start);
			start = end + 1;
		}
		end++;
	}
	commands[i++] = ft_strndup(&input[start], ft_strlen(&input[start]));
	commands[i] = NULL;
	return (commands);
}

void	execute_piped_commands(char **commands, t_shell *shell)
{
	int		i;
	char	**tokens;
	int		next_command;

	i = -1;
	shell->is_piped = (commands[1] != NULL);
	while (commands[++i])
	{
		tokens = tokenize_input(commands[i], shell);
		if (skip_empty_token(tokens))
			continue ;
		if (handle_heredoc_redirection(tokens, shell) < 0)
			return (perror("open failed for heredoc"), ft_free_tab(tokens));
		if (skip_empty_token(tokens))
			continue ;
		next_command = (commands[i + 1] != NULL);
		if (next_command && pipe(shell->fd) == -1)
			return (perror("pipe failed"), ft_free_tab(tokens));
		handle_pipe_process(tokens, shell, next_command);
		ft_free_tab(tokens);
	}
	while (wait(NULL) > 0)
		;
}

void	execute_child_process(char **tokens, t_shell *shell, int has_cmd)
{
	if (shell->heredoc_fd != -1 && shell->input_fd == 0)
	{
		dup2(shell->heredoc_fd, STDIN_FILENO);
		close(shell->heredoc_fd);
	}
	else if (shell->input_fd != 0)
	{
		dup2(shell->input_fd, STDIN_FILENO);
		close(shell->input_fd);
	}
	if (has_cmd)
	{
		dup2(shell->fd[1], STDOUT_FILENO);
		close(shell->fd[0]);
		close(shell->fd[1]);
	}
	if (handle_redirections(tokens, shell) < 0)
	{
		shell->exit_code = 1;
		perror("Redirection failed");
		exit(shell->exit_code);
	}
	execute_builtins(tokens, shell);
	exit(shell->exit_code);
}

void	execute_parent_process(t_shell *shell, int has_cmd)
{
	if (shell->input_fd != 0)
		close(shell->input_fd);
	if (has_cmd)
	{
		close(shell->fd[1]);
		shell->input_fd = shell->fd[0];
	}
	else
		shell->input_fd = 0;
	shell->is_piped = 0;
}

void	handle_pipe_process(char **tokens, t_shell *shell, int next_command)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_child_process(tokens, shell, next_command);
	else if (pid < 0)
	{
		perror("fork failed");
		shell->exit_code = 1;
	}
	else
		execute_parent_process(shell, next_command);
}
