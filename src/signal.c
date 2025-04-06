/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:08:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/06 16:17:45 by mmonika          ###   ########.fr       */
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
	}
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

int	count_pipes(const char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	*expand_segment(char *input, int *i, t_shell *shell)
{
	char	quote;
	char	*segment;
	int		start;

	segment = ft_calloc(1, 1);
	if (!segment)
		return (NULL);
	while (input[*i])
	{
		if (!quote && (input[*i] == '"' || input[*i] == '\''))
			quote = input[(*i)++];
		else if (quote && input[*i] == quote)
		{
			segment = ms_strjoin(segment, ft_substr(input, (*i)++, 1));
			break ;
		}
		else if (input[*i] == '$' && quote != '\'')
			segment = ms_strjoin(segment, get_value(input, i, shell));
		else
		{
			start = (*i)++;
			segment = ms_strjoin(segment, ft_substr(input, start, 1));
		}
	}
	return (segment);
}

/*
	SIGINIT == ctl_C
	SIGQUIT == ctl_\
	terminal.c_cc[VQUIT] = _POSIX_VDISABLE;	disable ctl_\
	terminal.c_lflag |= ECHOE | ICANON; 	enable canonical mode
*/