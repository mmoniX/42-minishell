/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:45:20 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/23 12:06:09 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_input_redirection(char **tokens, int *i)
{
	int	fd;

	if (!tokens[*i + 1])
	{
		ft_putstr_fd("missing file for input redirection\n", STDERR_FILENO);
		return (-1);
	}
	fd = open(tokens[*i + 1], O_RDONLY);
	if (fd < 0)
		return (perror("minishell: input redirection failed"), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	*i += 1;
	return (0);
}

int	handle_output_redirection(char **tokens, int *i, int append)
{
	int	flags;
	int	fd;

	if (!tokens[*i + 1])
		return (ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO), -1);
	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC); //ternari
	fd = open(tokens[*i + 1], flags, 0644);
	if (fd < 0)
		return (perror("minishell:redirection failed"), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	*i += 1;
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("minishell: heredoc file creation failed"), -1);
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
		return (perror("minishell: heredoc read failed"), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("/tmp/minishell_heredoc");
	return (0);
}
