/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_define.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:24:34 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/04 18:49:14 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*env_str(char *key, t_shell *shell)
{
	char	*value;

	value = get_env(key, shell->env);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

char	*get_value(char *input, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = ++(*i);
	if (input[start] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_code));
	}
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var_name = ft_substr(input, start, (*i) - start);
	var_value = env_str(var_name, shell);
	free(var_name);
	return (var_value);
}

char	*ms_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc (len * sizeof(char));
	if (!str)
		return (free (s1), NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	free(s1);
	free(s2);
	return (str);
}

char	*expand_variables(char *input, t_shell *shell)
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalnum(input[i + 1])
				|| input[i + 1] == '_' || input[i + 1] == '?'))
		{
			temp = get_value(input, &i, shell);
			result = ms_strjoin(result, temp);
			free(temp);
		}
		else
		{
			temp = ft_substr(input, i, 1);
			result = ms_strjoin(result, temp);
			i++;
		}
	}
	return (result);
}
