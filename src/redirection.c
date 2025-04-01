/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:45:20 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/01 19:45:41 by mmonika          ###   ########.fr       */
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

int handle_redirections(char **tokens)
{
    int i;
	int	j;
	
	i = 0;
	j = 0;
    while (tokens[i])
    {
		if (ft_strcmp(tokens[i], "<<") == 0)
        {
			if (handle_heredoc(tokens[i + 1], 0))
				return (FAIL);
			i += 2;
		}
        else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
        {
			if (output_redirection(tokens, &i, ft_strcmp(tokens[i], ">>") == 0))
				return(FAIL);
			i++;
        }
        else if (ft_strcmp(tokens[i], "<") == 0)
        {
			if (input_redirection(tokens, &i))
				return (FAIL);
			i++;
        }
        else
            tokens[j++] = tokens[i++];
    }
	tokens[j] = NULL;
    return (SUCCESS);
}

void execute_redirection(char **tokens, t_shell *shell)
{
    int		i;
	int		j;
	int		cmd_index;
	char	**cmd;

	i = 0;
    cmd = ft_calloc(1024, sizeof(char *));
    if (!cmd)
        return (perror("execute_redirection: malloc failed"));
    if (handle_redirections(tokens) < 0)
        return (ft_putstr_fd("Redirection failed!\n", STDERR_FILENO), free(cmd));
    i = 0;
    cmd_index = 0;
    while (tokens[i])
        cmd[cmd_index++] = ft_strdup(tokens[i++]);
    cmd[cmd_index] = NULL;
    if (is_builtin(cmd[0]))
        execute_builtin(cmd, shell);
    else
    {
        ft_execvp(cmd[0], cmd, shell->env);
		shell->exit_code = 127;
        return (perror("execvp failed"));
    }
	j = -1;
    while (++j < cmd_index)
        free(cmd[j]);
    free(cmd);
	exit (1);
}

// int handle_redirections(char **tokens)
// {
//     int i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
//     while (tokens[i])
//     {
//         if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
//         {
//             if (output_redirection(tokens, &i, ft_strcmp(tokens[i], ">>") == 0))
//                 return -1;
// 			i++;
//         }
//         else if (ft_strcmp(tokens[i], "<") == 0)
//         {
//             if (input_redirection(tokens, &i))
//                 return -1;
// 			i++;
//         }
//         else
//             tokens[j++] = tokens[i++];
//     }
// 	tokens[j] = NULL;
//     return (SUCCESS);
// }
