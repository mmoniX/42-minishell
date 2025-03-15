/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/15 11:47:15 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
	char *input;
	char **tokens;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("\nExiting minishell...\n");
			break;
		}
	
		if (*input)
			add_history(input);
	
		tokens = tokenize_input(input);
		if (!tokens)  // Prevent passing NULL tokens to execute_command
		{
			free(input);
			continue;
		}
	
		execute_command(tokens, env);
	
		ft_free_tab(tokens);
		free(input);
	}
	
    return 0;
}
