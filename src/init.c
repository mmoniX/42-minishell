/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:41:01 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/17 12:05:41 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**tokenize_input(char *input)
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	if (!tokens)
		exit (1);
	return (tokens);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
            continue;
        ft_strcpy(path_part, allpath[i]);
        ft_strcat(path_part, "/");
        ft_strcat(path_part, cmd);
        if (access(path_part, F_OK | X_OK) == 0)
            return (ft_free_tab(allpath), path_part);
        free(path_part);
	}
	return (ft_free_tab(allpath), NULL);
}


void	execute_command(char **tokens, char **env, t_shell *minishell)
{
	pid_t 	pid;
	int		status;
	char	*cmd_path;

	if (!tokens[0])
		return ;
	if (is_builtin(tokens[0]))
	{
		execute_builtin(tokens, minishell);
		return ;
	}
	cmd_path = get_path(tokens[0], env);
	if (!cmd_path)
	{
		printf("minishell: command not found: \n");
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, tokens, env) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else
		waitpid(pid, &status, 0);
	free(cmd_path);
}
