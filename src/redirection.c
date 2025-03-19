/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:45:20 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/17 15:46:20 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int handle_input_redirection(char **tokens, int *i)
{
    if (!tokens[*i + 1])
    {
        fprintf(stderr, "minishell: syntax error: missing file for input redirection\n");
        return -1;
    }

    // Open the file for reading
    int fd = open(tokens[*i + 1], O_RDONLY, 0777);
    if (fd < 0)
    {
        perror("minishell: input redirection failed");
        return -1;
    }

    // Redirect stdin to the opened file
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("minishell: dup2 failed");
        close(fd);
        return -1;
    }

    close(fd); // Close file descriptor after redirection
    return 0;
}

int handle_output_redirection(char **tokens, int *i, int append)
{
    int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    int fd = open(tokens[*i + 1], flags, 0644);
    
    if (fd < 0)
    {
        perror("minishell: output redirection failed");
        return -1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

int handle_heredoc(char *delimiter)
{
    char *line;
    int fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("minishell: heredoc file creation failed");
        return -1;
    }
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0)
            break;
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    close(fd);
    fd = open("/tmp/minishell_heredoc", O_RDONLY);
    if (fd < 0)
    {
        perror("minishell: heredoc read failed");
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}
