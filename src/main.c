/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/19 14:20:03 by mmonika          ###   ########.fr       */
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

// void	parse_env(t_minishell *minishell, char **env)
// {
// 	int	i;

// 	i = 0;
// 	minishell->env = dlist_new(ft_strdup(env[i]));
// 	while (env[++i])
// 		dlist_add_back(&minishell->env, dlist_new(ft_strdup(env[i])));
// }



int main(int ac, char **av, char **env)
{
    char	*input;
    char	**tokens;
	int		i;
	t_shell	*minishell;

	if (ac != 1)
		return (printf("Invalid Input\n"), 0);
	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (printf("Memory allocation failed\n"), 1);
	signal_handler();
	minishell->denv = convert_env_to_list(env);
	minishell->exit_code = 0;

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



