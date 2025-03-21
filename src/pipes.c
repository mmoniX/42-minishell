/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/21 12:39:20 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void execute_redirection(char **tokens, t_shell *shell)
{
    int i = 0;
    char **cmd = calloc(1024, sizeof(char *));
    int cmd_index = 0;

    if (!cmd)
    {
        perror("malloc failed");
        exit(1);
    }

    // Debugging: Print tokens
    for (int j = 0; tokens[j] != NULL; j++)
        printf("Token[%d]: %s\n", j, tokens[j]);

    while (tokens[i] != NULL) // Ensure tokens[i] is non-NULL
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
            cmd[cmd_index++] = strdup(tokens[i]); // Copy tokens[i]
            i++;
        }
    }

    cmd[cmd_index] = NULL;

    // Debugging: Print parsed command
    // for (int j = 0; cmd[j] != NULL; j++)
    //     printf("CMD[%d]: %s\n", j, cmd[j]);

    execvp(cmd[0], cmd);
    perror("execvp failed");

    // Free allocated memory before exiting
    for (int j = 0; j < cmd_index; j++)
        free(cmd[j]);
    free(cmd);

    exit(1);
}


void execute_piped_commands(char **commands, t_shell *shell)
{
    int i = 0, fd[2], input_fd = 0;
    pid_t pid;
	int j = 0;
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
		while (tokens[j] != NULL)
        {
            if (strcmp(tokens[j], "<<") == 0 && tokens[j + 1])
            {
                handle_heredoc(tokens[j + 1]);
                heredoc_fd = open("/tmp/minishell_heredoc", O_RDONLY);
                tokens[j] = NULL;
                tokens[j + 1] = NULL;
            }
			j++;
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
        pid = fork();
        if (pid == 0)
        {
			if (heredoc_fd != -1)
			{
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
				heredoc_fd = -1;
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
            execute_redirection(tokens, tokens);
            exit(shell->last_exit_status);
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

