/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/03 15:50:15 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

void	init_shell(t_shell *shell, char **env)
{
	shell->denv = convert_env_to_list(env);
	shell->env = env;
	shell->exit_code = 0;
	shell->old_pwd = NULL;
	shell->heredoc_fd = -1;
	shell->input_fd = 0;
	shell->is_piped = 0;
}

// void reset_terminal_state(void)
// {
//     struct termios term;

//     if (tcgetattr(STDIN_FILENO, &term) == -1)
//         perror("tcgetattr failed");
//     else
//     {
//         term.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo
//         if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
//             perror("tcsetattr failed");
//     }
// }

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	char	*input;

	(void)av;
	if (ac != 1)
		return (printf("Invalid Input\n"), 0);
	signal_handler();
	init_shell(&shell, env);
	while (1)
	{
		input = readline("\033[33mminishell$ \033[0m");
		if (!input || ft_strncmp(input, "exit", 4) == 0)
		{
			shell.exit_code = ft_exit(&shell, input);
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		process_input(&shell, input);
		free(input);
	}
	return (shell.exit_code);
}
