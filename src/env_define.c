/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_define.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:24:34 by gahmed            #+#    #+#             */
/*   Updated: 2025/04/07 15:39:20 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_denv(char *key, t_dlist *denv)
{
	t_dlist	*current;
	int		len;
	char	*env;

	current = denv;
	len = ft_strlen(key);
	while (current)
	{
		env = (char *)current->content;
		if (ft_strncmp(env, key, len) == 0 && env[len] == '=')
			return (env + len + 1);
		current = current->next;
	}
	return (NULL);
}

char	*env_str(char *key, t_shell *shell)
{
	char	*value;

	value = get_denv(key, shell->denv);
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
	char	*segment;
	int		i;

	i = 0;
	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			temp = ft_substr(input, i, 1);
			result = ms_strjoin(result, temp);
			segment = expand_segment(input, &i, shell);
		}
		else if (input[i] == '$')
			segment = get_value(input, &i, shell);
		else
			segment = ft_substr(input, i++, 1);
		result = ms_strjoin(result, segment);
	}
	return (result);
}
