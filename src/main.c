/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/15 14:59:12 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	global_signal = 0;

int main(int ac, char **av, char **env)
{
    char	*input;
    char	**tokens;
	int		i;

	if (ac != 1)
		return (printf("Invalid Input\n"), 0);
	signal_handler();
    while (1)
    {
        input = readline("minishell$ ");
        if (!input || ft_strcmp(input, "exit") == 0)
        {
			free(input);
            break ;
        }
        if (*input)
            add_history(input);
		tokens = tokenize_input(input);
		execute_command(tokens, env);
		// for Debug: Print tokens (remove later)
        i = 0;
		while (tokens[i])
		{
			printf("Token[%d]: %s\n", i, tokens[i]);
			i++;	
		}
		// Free allocated memory
		i = -1;
		while (tokens[++i])
			free(tokens[i]);
		free(tokens);
        free(input);
    }
    return 0;
}
