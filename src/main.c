/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/17 11:41:11 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


char **split_pipes(char *input)
{
    char **commands;
    char *token;
    int i = 0;

    // Allocate memory for commands array (assuming a reasonable max number of pipes)
    commands = malloc(sizeof(char *) * 1024);
    if (!commands)
    {
        perror("malloc failed");
        return NULL;
    }

    // Use `strtok` to split the input string by `|`
    token = strtok(input, "|");
    while (token)
    {
        while (*token == ' ') // Trim leading spaces
            token++;

        commands[i] = strdup(token);
        if (!commands[i])
        {
            perror("strdup failed");
            free(commands);
            return NULL;
        }
        i++;
        token = strtok(NULL, "|");
    }
    commands[i] = NULL; // NULL-terminate the array

    return commands;
}

int main(int ac, char **av, char **env)
{
    t_shell shell;
    char *input = NULL;
    char **tokens;
    char **commands;

    (void)ac;
    (void)av;
    shell.env = env;
    shell.last_exit_status = 0;
    
    while (1)
    {
        input = readline("minishell$ ");
        if (!input || ft_strcmp(input, "exit") == 0)
        {
            printf("Exiting minishell...\n");
            free(input);
            break;
        }

        if (*input)
            add_history(input);

        char *expanded_input = expand_variables(input, shell.env);
        char *final_input = expand_exit_status(expanded_input, &shell);
        free(expanded_input);

        if (!final_input || !*final_input) // Check for empty input
        {
            free(input);
            continue;
        }

        // ✅ Use `strdup` before `split_pipes` to avoid `strtok` modifying original input
        char *final_input_copy = strdup(final_input);
        if (!final_input_copy)
        {
            free(final_input);
            free(input);
            continue;
        }

        if (ft_strchr(final_input, '|'))
        {
            commands = split_pipes(final_input_copy);
            if (commands)
            {
                execute_piped_commands(commands, &shell);
                ft_free_tab(commands);
            }
        }
        else
        {
            tokens = tokenize_input(final_input);
            if (tokens && tokens[0])
                execute_command(tokens, &shell);
            ft_free_tab(tokens);
        }

        free(final_input);
        free(final_input_copy);
        free(input);
    }
    return shell.last_exit_status;
}



