/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/26 16:59:38 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**split_pipes(char *input)
{
	char	**commands;
	char	*token;
	int		i;

	i = 0;
	commands = malloc(sizeof(char *) * 1024);
	if (!commands)
		return (perror("malloc failed"), NULL);
	token = strtok(input, "|");
	while (token)
	{
		while (*token == ' ')
			token++;
		commands[i] = strdup(token);
		if (!commands[i])
			return (perror("strdup failed"), free(commands), NULL);
		i++;
		token = strtok(NULL, "|");
	}
	commands[i] = NULL;
	return (commands);
}

void execute_piped_commands(char **commands, t_shell *shell)
{
    int i;
    int j;
    int k;
    pid_t pid;
    t_exec exec_data;
	char	**tokens;
	int next_command;

	exec_data.input_fd = 0;
	exec_data.heredoc_fd = -1;
	exec_data.shell = shell;
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
            if (strcmp(tokens[j], "<<") == 0 && tokens[j + 1])
            {
                handle_heredoc(tokens[j + 1]);
                exec_data.heredoc_fd = open("/tmp/minishell_heredoc", O_RDONLY);
                if (exec_data.heredoc_fd == -1)
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
            if (pipe(exec_data.fd) == -1)
            {
                perror("pipe failed");
                ft_free_tab(tokens);
                return;
            }
        }
        // Fork to create a child process
        pid = fork();
        if (pid == 0)
		{
			if (exec_data.heredoc_fd != -1 && i == 0)
			{
				dup2(exec_data.heredoc_fd, STDIN_FILENO);
				close (exec_data.heredoc_fd);
			}
			execute_child_process(tokens, &exec_data, next_command);
		}
        else if (pid < 0)
        {
            perror("fork failed");
            shell->exit_code = 1;
            return;
        }
        else
			execute_parent_process(&exec_data, next_command);
        ft_free_tab(tokens);
        i++;
    }
    while (wait(NULL) > 0);
	unlink("/tmp/minishell_heredoc");
}

void execute_child_process(char **tokens, t_exec *exec_data, int has_cmd)
{
    if (exec_data->heredoc_fd != -1 && exec_data->input_fd == 0)
    {
        dup2(exec_data->heredoc_fd, STDIN_FILENO);
        close(exec_data->heredoc_fd);
    }
    else if (exec_data->input_fd != 0)
    {
        dup2(exec_data->input_fd, STDIN_FILENO);
        close(exec_data->input_fd);
    }
    if (has_cmd)
    {
        dup2(exec_data->fd[1], STDOUT_FILENO);
        close(exec_data->fd[0]);
        close(exec_data->fd[1]);
    }
    execute_redirection(tokens, exec_data->shell);
    if (is_builtin(tokens[0]))
        execute_builtin(tokens, exec_data->shell);
    else
    {
        ft_execvp(tokens[0], tokens, exec_data->shell->env);
        perror("execvp failed");
        exit(127);
    }
}

void execute_parent_process(t_exec *exec_data, int has_cmd)
{
    if (exec_data->input_fd != 0)
        close(exec_data->input_fd);

    if (has_cmd)
    {
        close(exec_data->fd[1]);
        exec_data->input_fd = exec_data->fd[0];
    }
}
