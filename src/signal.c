/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:08:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/04 19:25:54 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_for_termination(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 1;
	}
	else if (sig == SIGQUIT)
		g_signal = 0;
}

void	signal_handler(void)
{
	struct sigaction	sa;
	struct termios		terminal;

	sa.sa_handler = signal_for_termination;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (tcgetattr(STDIN_FILENO, &terminal) != 0)
		return (perror("Terminal Error"));
	terminal.c_cc[VQUIT] = _POSIX_VDISABLE;
	terminal.c_lflag |= ECHOE | ICANON;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) != 0)
		return (perror("Terminal Error"));
}

void	ft_free_token(char **token)
{
	if (*token)
	{
		free(*token);
		*token = NULL;
	}
}

/*
	SIGINIT == ctl_C
	SIGQUIT == ctl_\
	terminal.c_cc[VQUIT] = _POSIX_VDISABLE;	disable ctl_\
	terminal.c_lflag |= ECHOE | ICANON; 	enable canonical mode
*/