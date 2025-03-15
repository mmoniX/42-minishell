/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/15 14:58:53 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int global_signal;

# define SUCCESS	0
# define FAIL		1

#ifndef MAX_TOKENS
#define MAX_TOKENS 100
#endif
struct	s_shell
{
	int	print;
	char	**env;
		
} t_shell;



//init and tokenize
char	**tokenize_input(char *input);
void	execute_command(char **tokens, char **env);
char	*get_path(char *cmd, char **env);
char	*get_env(char *key, char **env);

//utils
void	ft_free_tab(char **tab);

/* signal */
void	signal_for_termination(int sig);
void	terminal_control(void);
void	signal_handler(void);

#endif