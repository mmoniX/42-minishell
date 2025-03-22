/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:24:34 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/21 16:17:43 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_env_variables(char *input, t_shell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		start;

	result = malloc(BUFSIZ);
	if (!result)
		return (perror("malloc failed in expand_env_variables"), NULL);
	i = 0;
	j = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
		{
			start = ++i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			var_name = ft_substr(input, start, i - start);
			var_value = get_env(var_name, shell->env);
			free(var_name);
			while (var_value && *var_value)
				result[j++] = *var_value++;
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	free(input);
	return (result);
}

char *expand_exit_status(char *input, t_shell *shell)
{
    char	*exit_status;
	char	*result;
	char	*position;
	
	position = ft_strstr(input, "$?");
	if (!position)
		return (ft_strdup(input));
	exit_status = ft_itoa(shell->exit_code);
	if (!exit_status)
		return (NULL);
	result = malloc(ft_strlen(input) + ft_strlen(exit_status) - 1);
    if (!result)
		return (perror("malloc failed: $?"), free(exit_status), NULL);
	ft_strncpy(result, input, position - input);
	result[position - input] = '\0';
	ft_strcat(result, exit_status);
	ft_strcat(result, position + 2);
	free (exit_status);
    return (result);
}

char	*expand_variables(char *input, t_shell *shell)
{
	char	*expanded_exit;
	char	*final_expansion;

	expanded_exit = expand_exit_status(input, shell);
	if (!expanded_exit)
		return (NULL);
	final_expansion = expand_env_variables(expanded_exit, shell);
	return (final_expansion);
}
