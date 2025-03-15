/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:52:38 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/14 14:53:04 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to expand environment variables in a string
char *expand_variable(char *arg, int last_exit_status, char **env)
{
    char *value;
    
    if (arg[0] == '$') // Check if it's an environment variable
    {
        if (arg[1] == '?') // Handle $?
            return (asprintf(&value, "%d", last_exit_status) != -1) ? value : NULL;

        value = getenv(arg + 1); // Get variable value
        return value ? strdup(value) : strdup(""); // Return value or empty string
    }
    return strdup(arg); // Return argument if not an env variable
}
