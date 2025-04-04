/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:54:41 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/04 16:05:33 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;

	if (!src)
		return (NULL);
	dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
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

int	ft_execvp(char *cmd, char **args, char **env)
{
	char	*full_path;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (execve(cmd, args, env));
	full_path = get_path(cmd, env);
	if (!full_path)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (FAIL);
	}
	if (execve(full_path, args, env) == -1)
	{
		perror("execve failed");
		free(full_path);
		return (FAIL);
	}
	free(full_path);
	return (SUCCESS);
}

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
	quoted_str = ft_strndup(&input[start], end - start);
	if (!quoted_str)
		return (NULL);
	*index = end + 1;
	return (quoted_str);
}

int	count_pipes(const char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}
