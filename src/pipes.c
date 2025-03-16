/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:06:41 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/16 16:14:11 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void execute_single_command(char **tokens, t_shell *shell)
{
    char *cmd_path;

    if (!tokens || !tokens[0]) {
        printf("No command to execute.\n");
        return;
    }
    if (ft_strcmp(tokens[0], "env") == 0) {
        builtin_env(shell->env);
        shell->last_exit_status = 0;
        return;
    }
    cmd_path = get_path(tokens[0], shell->env);
    if (!cmd_path) {
        fprintf(stderr, "minishell: command not found: %s\n", tokens[0]);
        shell->last_exit_status = 127;
        return;
    }
    if (execve(cmd_path, tokens, shell->env) == -1) {
        perror("execve failed");
        shell->last_exit_status = 127;
        return;
    }
}

void execute_piped_commands(char **commands, t_shell *shell)
{
    int i = 0, fd[2], input_fd = 0;
    pid_t pid;

    while (commands[i])
    {
        char **tokens = tokenize_input(commands[i]);
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            dup2(input_fd, STDIN_FILENO);
            if (commands[i + 1])
                dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
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
        close(fd[1]);
        input_fd = fd[0];
        i++;
    }
    while (wait(NULL) > 0);
}
