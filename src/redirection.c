/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:45:20 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/02 14:32:32 by mmonika          ###   ########.fr       */
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

int	output_redirec(char **tokens, int *i, int append)
{
	int	fd;

	if (!tokens[*i + 1])
		return (ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO), FAIL);
	if (append)
		fd = open(tokens[*i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(tokens[*i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Output redirection failed"), FAIL);
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
		return (perror("Heredoc file creation failed"), FAIL);
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
		return (perror("Heredoc read failed"), FAIL);
	if (!is_piped)
		return (dup2(fd, STDIN_FILENO), close(fd), SUCCESS);
	else
		return (fd);
}

int	handle_heredoc_redirection(char **tokens, t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
		{
			shell->heredoc_fd = handle_heredoc(tokens[i + 1], shell->is_piped);
			if (shell->heredoc_fd == -1)
				return (FAIL);
			j = i;
			while (tokens[j + 2])
			{
				tokens[j] = tokens[j + 2];
				j++;
			}
			tokens[j] = NULL;
		}
		else
			i++;
	}
	return (SUCCESS);
}

int	handle_redirections(char **tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	handle_heredoc_redirection(tokens, shell);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
		{
			if (output_redirec(tokens, &i, ft_strcmp(tokens[i], ">>") == 0) < 0)
				return (FAIL);
			i++;
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			if (input_redirection(tokens, &i) < 0)
				return (FAIL);
			i++;
		}
		else
			tokens[j++] = tokens[i++];
	}
	tokens[j] = NULL;
	return (SUCCESS);
}
