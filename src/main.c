/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <mmonika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:37 by codespace        ###   ########.fr       */
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
		execute_command(tokens, env, minishell);
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
