/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/19 15:41:20 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	global_signal = 0;

t_dlist	*convert_env_to_list(char **env)
{
	t_dlist	*temp;
	t_dlist	*current;
	int		i;

	if (!env || !*env)
		return (NULL);
	temp = ft_dlstnew(env[0]);
	current = temp;
	i = 1;
	while (env[i])
	{
		current->next = ft_dlstnew(ft_strdup(env[i]));
		current->next->prev = current;
		current = current->next;
		i++;
	}
	return (temp);
}

char **split_pipes(char *input)
{
    char **commands;
    char *token;
    int i = 0;
    commands = malloc(sizeof(char *) * 1024);
    if (!commands)
    {
        perror("malloc failed");
        return NULL;
    }
    token = strtok(input, "|");
    while (token)
    {
        while (*token == ' ')
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
    commands[i] = NULL;

    return commands;
}

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
    shell.last_exit_status = 0;
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

        char *expanded_input = expand_variables(input, shell.env);
        char *final_input = expand_exit_status(expanded_input, &shell);
        free(expanded_input);

        if (!final_input || !*final_input)
        {
            free(input);
            continue;
        }
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



