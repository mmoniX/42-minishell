/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:24:34 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/21 15:24:20 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *expand_variables(char *input, char **env)
{
    char	*result;
	int		i;
	int		j;
	

	result = malloc(BUFSIZ);
    if (!result)
		return (perror("malloc failed in expand_variables"), NULL);
    i = 0;
	j = 0;
    while (input[i])
    {
        if (input[i] == '$' && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
        {
            int start = ++i;
            while (ft_isalnum(input[i]) || input[i] == '_')
                i++;
            char *var_name = ft_strndup(&input[start], i - start);
            char *var_value = get_env(var_name, env);
            free(var_name);
            if (var_value)
            {
                while (*var_value)
                    result[j++] = *var_value++;
            }
        }
        else
            result[j++] = input[i++];
    }
    result[j] = '\0';
    return (result);
}

char *expand_exit_status(char *input, t_shell *shell)
{
    char	exit_str[10];
	char	*result;
	int		i;
	int		j;
	int		k;
	
	result = malloc(BUFSIZ);
    if (!result)
		return (perror("malloc failed in expand_variables"), NULL);
    i = 0;
	j = 0;
    while (input[i])
    {
        if (input[i] == '$' && input[i + 1] == '?')
        {
            i += 2;
            sprintf(exit_str, "%d", shell->last_exit_status);
            k = 0;
            while (exit_str[k])
                result[j++] = exit_str[k++];
        }
        else
            result[j++] = input[i++];
    }
    result[j] = '\0';
    return (result);
}
