/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:24:34 by gahmed            #+#    #+#             */
/*   Updated: 2025/03/15 12:38:16 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *expand_variables(char *input, char **env)
{
    char *result = malloc(BUFSIZ); // Allocate buffer for expanded string
    if (!result)
        return NULL;

    int i = 0, j = 0;
    while (input[i])
    {
        if (input[i] == '$' && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
        {
            int start = ++i;
            while (ft_isalnum(input[i]) || input[i] == '_')  // Extract variable name
                i++;

            char *var_name = strndup(&input[start], i - start);
            char *var_value = get_env(var_name, env);
            free(var_name);

            if (var_value)
            {
                while (*var_value)  // Copy variable value
                    result[j++] = *var_value++;
            }
        }
        else
        {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}

char *expand_exit_status(char *input)
{
    char *result = malloc(BUFSIZ);
    if (!result)
        return NULL;

    int i = 0, j = 0;
    while (input[i])
    {
        if (input[i] == '$' && input[i + 1] == '?')  // Detect $?
        {
            i += 2;
            char exit_str[10];
            sprintf(exit_str, "%d", g_last_exit_status);  // Convert to string
            int k = 0;
            while (exit_str[k])
                result[j++] = exit_str[k++];
        }
        else
        {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}
