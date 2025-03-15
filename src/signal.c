/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:08:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/15 15:09:58 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_for_termination(int sig)
{
	if (sig == SIGINT) //ctl_C
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0); /* to remove ^C */
		rl_redisplay();
		global_signal = 1;
	}
	else if (sig == SIGQUIT) //ctl_D
	{
		rl_on_new_line();
		rl_redisplay();
		global_signal = 0;
	}
}
void	terminal_control(void)
{
	struct termios terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) != 0)
		return(perror("Terminal Error"));
	else
	{
		terminal.c_cc[VQUIT] = _POSIX_VDISABLE;
		terminal.c_lflag |= ECHOE | ICANON;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) != 0)
			return(perror("Terminal Error"));
		if (tcgetattr(STDIN_FILENO, &terminal) != 0)
			return(perror("Terminal Error"));
	}
}

void	signal_handler(void)
{
	struct sigaction sa;
	
	sa.sa_handler = signal_for_termination;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	terminal_control();
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
