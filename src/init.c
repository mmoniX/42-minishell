/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/21 14:01:51 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*handle_quotes(const char *input, int *index, char quote_type)
{
	int		start;
	int		end;
	char	*quoted_str;

	start = *index + 1;
	end = start;
	while (input[end] && input[end] != quote_type)
		end++;
	if (input[end] != quote_type)
	{
		ft_putstr_fd("Error: Unclosed quote\n", STDERR_FILENO);
		return (NULL);
	}
	quoted_str = strndup(&input[start], end - start); //strndup not allowed
	*index = end + 1;
	return (quoted_str);
}

char	**tokenize_input(char *input)
{
	char	**tokens;
	char	*quoted_str;
	int		start;
	int		i;
	int		j;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (perror("malloc failed for tokens"), NULL);
	i = 0;
	j = 0;
	while (input[i] && j < MAX_TOKENS - 1)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			tokens[j++] = ft_strdup("|");
			i++;
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			quoted_str = handle_quotes(input, &i, input[i]);
			if (!quoted_str)
				return (free(tokens), NULL);
			tokens[j++] = quoted_str;
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' '
				&& input[i] != '|' && input[i] != '"' && input[i] != '\'')
				i++;
			tokens[j] = strndup (&input[start], i - start); //strndup not allowed
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

char	*get_env(char *key, char **env)
{
	int		i;
	int		j;
	char	*prefix;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		prefix = ft_substr(env[i], 0, j);
		if (ft_strcmp(prefix, key) == 0)
		{
			free(prefix);
			return (env[i] + j + 1);
		}
		free(prefix);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	allpath = ft_split(get_env("PATH", env), ':');
	if (!allpath)
		return (NULL);
	while (allpath[++i])
	{
		path_part = malloc(ft_strlen(allpath[i]) + ft_strlen(cmd) + 2);
		if (!path_part)
			continue ;
		ft_strcpy(path_part, allpath[i]);
		ft_strcat(path_part, "/");
		ft_strcat(path_part, cmd);
		if (access(path_part, F_OK | X_OK) == 0)
			return (ft_free_tab(allpath), path_part);
		free(path_part);
	}
	return (ft_free_tab(allpath), NULL);
}

void	execute_command(char **tokens, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (!tokens || !tokens[0])
	{
		printf("No command to execute.\n");
		return ;
	}
	if (is_builtin(tokens[0]))
	{
		execute_builtin(tokens, shell);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execute_redirection(tokens, shell);
		exit(shell->exit_code);
	}
	else if (pid < 0)
	{
		perror("fork failed");
		shell->exit_code = 1;
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}
