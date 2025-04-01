/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:45:20 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/01 11:51:29 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	input_redirection(char **tokens, int *i)
{
	int	fd;

	if (!tokens[*i + 1])
	{
		ft_putstr_fd("missing file for input redirection\n", STDERR_FILENO);
		return (FAIL);
	}
	fd = open(tokens[*i + 1], O_RDONLY);
	if (fd < 0)
		return (perror("Input redirection failed"), FAIL);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("Input redirection: dup2 failed"), close(fd), FAIL);
	close(fd);
	*i += 1;
	return (SUCCESS);
}

int	output_redirection(char **tokens, int *i, int append)
{
	int	fd;

	if (!tokens[*i + 1])
		return (ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO), FAIL);
	if (append)
		fd = open(tokens[*i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(tokens[*i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Output redirection failed"), close(fd), FAIL);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("Output redirection: dup2 failed"), close(fd), FAIL);
	close(fd);
	*i += 1;
	return (SUCCESS);
}

int	handle_heredoc(char *delimiter, int is_piped)
{
	char	*line;
	int		fd;

	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Heredoc file creation failed"), close(fd), FAIL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	fd = open("/tmp/minishell_heredoc", O_RDONLY);
	if (fd < 0)
		return (perror("Heredoc read failed"), close(fd), FAIL);
	if (!is_piped)
		return (dup2(fd, STDIN_FILENO), close(fd), SUCCESS);
	else
		return (fd);
}

void execute_redirection(char **tokens, t_shell *shell)
{
    int i = 0, j = 0;
    char **cmd = calloc(1024, sizeof(char *));
    if (!cmd)
    {
        perror("malloc failed");
        exit(1);
    }
    while (tokens[i])
    {
        if (strcmp(tokens[i], "<<") == 0) // Handle heredoc
        {
            if (!tokens[i + 1])
            {
                fprintf(stderr, "minishell: syntax error: missing delimiter for heredoc\n");
                free(cmd);
                exit(1);
            }
            if (handle_heredoc(tokens[i + 1], 0) < 0)
            {
                fprintf(stderr, "minishell: heredoc failed\n");
                free(cmd);
                return;
            }
            i += 2; // Skip `<<` and its delimiter
        }
        else
            tokens[j++] = tokens[i++];
    }
    tokens[j] = NULL;
    if (handle_redirections(tokens) < 0)
    {
        fprintf(stderr, "Redirection failed!\n");
        free(cmd);
        return;
    }
    i = 0;
    int cmd_index = 0;
    while (tokens[i])
        cmd[cmd_index++] = strdup(tokens[i++]);
    cmd[cmd_index] = NULL;

    if (is_builtin(cmd[0]))
        execute_builtin(cmd, shell);
    else
    {
        ft_execvp(cmd[0], cmd, shell->env);
        perror("execvp failed");
    }

    for (int j = 0; j < cmd_index; j++)
        free(cmd[j]);
    free(cmd);
    exit(1);
}

int handle_redirections(char **tokens)
{
    int i;
	int	j;
	
	i = 0;
	j = 0;
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
        {
            if (output_redirection(tokens, &i, ft_strcmp(tokens[i], ">>") == 0))
                return -1;
			i++;
        }
        else if (ft_strcmp(tokens[i], "<") == 0)
        {
            if (input_redirection(tokens, &i))
                return -1;
			i++;
        }
        else
            tokens[j++] = tokens[i++];
    }
	tokens[j] = NULL;
    return (SUCCESS);
}
