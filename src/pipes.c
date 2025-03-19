/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/19 11:56:45 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void execute_single_command(char **tokens, t_shell *shell)
// {
//     char *cmd_path;

//     if (!tokens || !tokens[0]) {
//         printf("No command to execute.\n");
//         return;
//     }
//     if (ft_strcmp(tokens[0], "env") == 0) {
//         builtin_env(shell->env);
//         shell->last_exit_status = 0;
//         return;
//     }
//     cmd_path = get_path(tokens[0], shell->env);
//     if (!cmd_path) {
//         fprintf(stderr, "minishell: command not found: %s\n", tokens[0]);
//         shell->last_exit_status = 127;
//         return;
//     }
//     if (execve(cmd_path, tokens, shell->env) == -1) {
//         perror("execve failed");
//         shell->last_exit_status = 127;
//         return;
//     }
// }

void execute_redirection(char **tokens, t_shell *shell)
{
    int i = 0;

    // Handle redirections
    while (tokens[i])
    {
        if (strcmp(tokens[i], "<") == 0)
        {
            if (handle_input_redirection(tokens, &i) < 0) return;
        }
        else if (strcmp(tokens[i], ">") == 0)
        {
            if (handle_output_redirection(tokens, &i, 0) < 0) return;
        }
        else if (strcmp(tokens[i], ">>") == 0)
        {
            if (handle_output_redirection(tokens, &i, 1) < 0) return;
        }
        else if (strcmp(tokens[i], "<<") == 0)
        {
            if (handle_heredoc(tokens[i + 1]) < 0) return;
        }
        else
        {
            i++;
        }
    }

    // Execute command
    execvp(tokens[0], tokens);
    perror("execvp failed");
    exit(1);
}


void execute_piped_commands(char **commands, t_shell *shell)
{
    int i = 0, fd[2], input_fd = 0;
    pid_t pid;

    while (commands[i])
    {
        char **tokens = tokenize_input(commands[i]);
        if (!tokens || !tokens[0])
        {
            ft_free_tab(tokens);
            i++;
            continue;
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
            if (input_fd != 0)
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
            execvp(tokens[0], tokens);
            perror("execvp failed");
            exit(1);
        }
        else if (pid < 0)
        {
            perror("fork failed");
            shell->last_exit_status = 1;
            return;
        }
        // Parent process
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

