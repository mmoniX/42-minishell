/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:54:41 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/24 13:28:56 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && src[i])
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
	char *full_path;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return execve(cmd, args, env);
	full_path = get_path(cmd, env);
	if (!full_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		return -1;
	}
	if (execve(full_path, args, env) == -1)
	{
		perror("execve failed");
		free(full_path);
		return -1;
	}
	free(full_path);
	return 0;
}
