/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/14 11:51:49 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    char	*input;
    char	**tokens;
	int		i;

	if (ac != 1)
		return (0);
    while (1)
    {
        input = readline("minishell$ ");
        
        // ft_strcmp have to use from libft
        if (!input || ft_strcmp(input, "exit") == 0)
        {
            printf("exit\n");
			free(input);
            break;
        }

        // If input is not empty, add it to history
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
