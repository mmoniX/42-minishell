/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:45 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/16 15:44:36 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* shall implement only -n or -nnnn ?? */
void	ft_echo(char **args, int fd)
{
	int	i;
	int	j;
	int	line;

	i = 1;
	line = 1;	
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
		line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd (args[i], fd);
		if (args[i + 1])
			ft_putstr_fd (" ", fd);
		i++;
	}
	if (line)
		ft_putstr_fd ("\n", fd);
}

int	ft_pwd(void)
{
	char	*directory;
	
	directory = getcwd (NULL, 0);
	if (!directory)
	{
		perror ("pwd error");
		return (free(directory), FAIL);
	}
	write(1, directory, ft_strlen(directory));
	free (directory);
	return (SUCCESS);
}

void	unset_util(t_shell *minishell, char *var)
{
	t_dlist	*current;
	size_t	len;
	char	*env_var;

	if (ft_strcmp(var, "_") == 0)
		return ;
	current = minishell->denv;
	len = ft_strlen(var);
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, var, len) == 0	&& env_var[len] == '=')
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == minishell->denv)
				minishell->denv = current->next;
			free (current->content);
			free (current);
			return ;
		}
		current = current->next;
	}
}

void	ft_unset(t_shell *minishell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_env(args[i]))
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd(" is invalid\n", STDERR_FILENO);
			minishell->exit_code = 1;
		}
		else
			unset_util(minishell, args[i]);
		i++;
	}
}
