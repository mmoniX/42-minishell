/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/21 16:06:12 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

int main(int ac, char **av, char **env)
{
    t_shell shell;
    char *input = NULL;
    char **tokens;
    char **commands;

	if (ac != 1)
		return (printf("Invalid Input\n"), 0);
	signal_handler();

	shell.denv = convert_env_to_list(env);
	shell.exit_code = 0;
    shell.env = env;
	shell.old_pwd = NULL;
    
    while (1)
    {
        input = readline("\033[33mminishell$ \033[0m");
        if (!input || ft_strcmp(input, "exit") == 0)
        {
            printf("Exiting minishell...\n");
            free(input);
            break;
        }

        if (*input)
            add_history(input);

        char *final_input = expand_variables(input, &shell); //check;
        if (!final_input || !*final_input)
        {
            free(input);
            continue;
        }
        char *final_input_copy = ft_strdup(final_input);
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
    return shell.exit_code;
}



