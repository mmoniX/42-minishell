/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/10 14:46:24 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    char	*input;

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
        free(input);
    }
    return 0;
}
