/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/16 16:17:12 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    t_shell shell;
    char *input = NULL;
    char **tokens;

    shell.env = env;
    shell.last_exit_status = 0;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input || strcmp(input, "exit") == 0)
        {
            printf("Exiting condition triggered\n");
            if (!input)
                printf("input is NULL\n");
            else
                printf("input is: %s\n", input);
            printf("\nExiting minishell...\n");
            free(input);
            break;
        }
        add_history(input);

        char *expanded_input = expand_variables(input, shell.env);
        char *final_input = expand_exit_status(expanded_input, &shell);
        free(expanded_input);
        if (!final_input)
        {
            free(input);
            continue;
        }
        tokens = tokenize_input(final_input);
        free(final_input);
        if (!tokens)
        {
            free(input);
            continue;
        }
        execute_command(tokens, &shell);
        ft_free_tab(tokens);
        free(input);
    }
    return shell.last_exit_status;
}


