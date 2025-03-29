/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/29 15:06:06 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**split_pipes(char *input)
{
	char	**commands;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	commands = malloc(sizeof(char *) * 1024);
	if (!commands)
		return (perror("malloc failed"), NULL);
	while (input[end])
	{
		if (input[end] == '|')
		{
			commands[i++] = ft_strndup(&input[start], end - start);
			start = end + 1;
		}
		end++;
	}
	commands[i++] = ft_strndup(&input[start], end - start);
	commands[i] = NULL;
	return (commands);
}

void	execute_piped_commands(char **commands, t_shell *shell)
{
    int		i;
    int		j;
    int		k;
    pid_t	pid;
	char	**tokens;
	int		next_command;

	i = 0;
    while (commands[i])
    {
        tokens = tokenize_input(commands[i]);
        if (!tokens || !tokens[0])
        {
            ft_free_tab(tokens);
            i++;
            continue;
        }
		j = 0;
        while (tokens[j] != NULL)
        {
            if (ft_strcmp(tokens[j], "<<") == 0 && tokens[j + 1])
            {
                shell->heredoc_fd = handle_heredoc(tokens[j + 1], shell->is_piped);
                if (shell->heredoc_fd == -1)
				{
                    perror("open failed for heredoc");
                    ft_free_tab(tokens);
                    return;
                }
				k = j;
                while (tokens[k + 2] != NULL)
				{
                	tokens[k] = tokens[k + 2];
					k++;
				}
                tokens[k] = NULL;
            }
			j++;
        }
		if(commands[i + 1])
			next_command = 1;
		else
			next_command = 0;
        if (next_command)
        {
            if (pipe(shell->fd) == -1)
			{
                perror("pipe failed");
                ft_free_tab(tokens);
                return;
            }
        }
        pid = fork();
        if (pid == 0)
		{
			if (shell->heredoc_fd != -1 && i == 0)
			{
				dup2(shell->heredoc_fd, STDIN_FILENO);
				close (shell->heredoc_fd);
			}
			execute_child_process(tokens, shell, next_command);
		}
        else if (pid < 0)
        {
            perror("fork failed");
            shell->exit_code = 1;
            return;
        }
        else
			execute_parent_process(shell, next_command);
        ft_free_tab(tokens);
        i++;
    }
    while (wait(NULL) > 0);
	unlink("/tmp/minishell_heredoc");
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
	execute_redirection(tokens, shell);
	if (is_builtin(tokens[0]))
		execute_builtin(tokens, shell);
	else
	{
		ft_execvp(tokens[0], tokens, shell->env);
		perror("execvp failed");
		shell->exit_code = 127;
	}
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
}
