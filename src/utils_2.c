/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:54:41 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/13 17:02:38 by mmonika          ###   ########.fr       */
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

char	*get_path(char *cmd, t_dlist *denv)
{
	int		i;
	char	**allpath;
	char	*path_part;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	allpath = ft_split(get_denv("PATH", denv), ':');
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

void	check_directory(char *cmd, t_shell *shell)
{
	DIR		*directory;

	directory = opendir(cmd);
	if (!cmd)
	{
		shell->exit_code = 1;
		return ;
	}
	if (directory != NULL)
	{
		closedir(directory);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		shell->exit_code = 126;
		return ;
	}
}

int	ft_execvp(char *cmd, char **args, t_shell *shell)
{
	char	*full_path;

	if (!cmd || *cmd == '\0')
		return (shell->exit_code = 127, FAIL);
	check_directory(cmd, shell);
	if (!get_denv("PATH", shell->denv)
		|| ft_strlen(get_denv("PATH", shell->denv)) == 0)
	{
		if (!ft_strchr(cmd, '/'))
		{
			perror(cmd);
			return (shell->exit_code = 127, FAIL);
		}
	}
	else if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (execve(cmd, args, shell->env));
	full_path = get_path(cmd, shell->denv);
	if (!full_path)
	{
		perror(cmd);
		return (shell->exit_code = 127, FAIL);
	}
	if (execve(full_path, args, shell->env) == -1)
		return (free(full_path), shell->exit_code = 126, FAIL);
	return (free(full_path), SUCCESS);
}
