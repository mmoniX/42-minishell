/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/21 16:00:16 by gahmed           ###   ########.fr       */
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

void execute_redirection(char **tokens, t_shell *shell)
{
    int i = 0, j = 0;
    char **cmd = calloc(1024, sizeof(char *));
    int cmd_index = 0;

    if (!cmd)
    {
        perror("malloc failed");
        exit(1);
    }
    // Debugging: Print tokens
    // for (int j = 0; tokens[j] != NULL; j++)
    //     printf("Token[%d]: %s\n", j, tokens[j]);
	
	//detect and handle pipes early
	while(tokens[j] != NULL)
	{
		if (strcmp(tokens[j], "|") == 0)
        {
            tokens[j] = NULL;
            execute_piped_commands(tokens, shell);
            free(cmd);
            return;
        }
		j++; 
	}
    while (tokens[i] != NULL)
    {
        if (tokens[i] && strcmp(tokens[i], "<") == 0)
        {
            if (tokens[i + 1] == NULL)
            {
                fprintf(stderr, "minishell: syntax error: missing file for input redirection\n");
                free(cmd);
                exit(1);
            }
            handle_input_redirection(tokens, &i);
            i++;
        }
        else if (tokens[i] && (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0))
        {
            if (tokens[i + 1] == NULL)
            {
                fprintf(stderr, "minishell: syntax error: missing file for output redirection\n");
                free(cmd);
                exit(1);
            }
            handle_output_redirection(tokens, &i, strcmp(tokens[i], ">>") == 0);
            i++;
        }
        else if (tokens[i] && strcmp(tokens[i], "<<") == 0)
        {
            if (tokens[i + 1] == NULL)
            {
                fprintf(stderr, "minishell: syntax error: missing delimiter for heredoc\n");
                free(cmd);
                exit(1);
            }
            handle_heredoc(tokens[i + 1]);
            i += 2;
        }
        else
        {
            cmd[cmd_index++] = strdup(tokens[i]);
            i++;
        }
    }
    cmd[cmd_index] = NULL;
    execvp(cmd[0], cmd);
    perror("execvp failed");
    for (int j = 0; j < cmd_index; j++)
        free(cmd[j]);
    free(cmd);
    exit(1);
}


void execute_piped_commands(char **commands, t_shell *shell)
{
    int i = 0, fd[2], input_fd = 0;
    pid_t pid;
    int heredoc_fd = -1;

    while (commands[i])
    {
        char **tokens = tokenize_input(commands[i]);
        if (!tokens || !tokens[0])
        {
            ft_free_tab(tokens);
            i++;
            continue;
        }
        for (int j = 0; tokens[j] != NULL; j++)
        {
            if (strcmp(tokens[j], "<<") == 0 && tokens[j + 1])
            {
                handle_heredoc(tokens[j + 1]);
                heredoc_fd = open("/tmp/minishell_heredoc", O_RDONLY);
                if (heredoc_fd == -1)
                {
                    perror("open failed for heredoc");
                    ft_free_tab(tokens);
                    return;
                }
                for (int k = j; tokens[k + 2] != NULL; k++)
                    tokens[k] = tokens[k + 2];
                tokens[j] = NULL;
            }
        }
        if (commands[i + 1])
        {
            if (pipe(fd) == -1)
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
            if (heredoc_fd != -1)
            {
                dup2(heredoc_fd, STDIN_FILENO);
                close(heredoc_fd);
            }
            else if (input_fd != 0)
            {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (commands[i + 1])
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            execute_redirection(tokens, shell);
            if (is_builtin(tokens[0]))
                execute_builtin(tokens, shell);
            else
            {
                execvp(tokens[0], tokens);
                perror("execvp failed");
                exit(127);
            }
        }
        else if (pid < 0)
        {
            perror("fork failed");
            shell->last_exit_status = 1;
            return;
        }
        if (input_fd != 0)
            close(input_fd);

        if (commands[i + 1])
        {
            close(fd[1]);
            input_fd = fd[0];
        }
        ft_free_tab(tokens);
        i++;
    }
    while (wait(NULL) > 0);
}
