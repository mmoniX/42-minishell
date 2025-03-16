/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/16 12:03:15 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
	char *input;
	char **tokens;
	t_shell shell;
	shell.last_exit_status = 0;
	shell.env = env;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			printf("\nExiting minishell...\n");
			break;
		}
		if (!input)
			break;
		add_history(input);
		char *expanded_input = expand_variables(input, env);
		char *final_input = expand_exit_status(expanded_input, &shell);
		free(expanded_input);
		if (!final_input)
			continue;
		tokens = tokenize_input(final_input);
		free(final_input);
		if (!tokens)
		{
			continue;
		}
		execute_command(tokens, &shell);
		ft_free_tab(tokens);
	}
	
    return 0;
}
