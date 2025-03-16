/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/16 11:59:41 by gahmed           ###   ########.fr       */
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
# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

#ifndef MAX_TOKENS
#define MAX_TOKENS 100
#endif
typedef struct	s_shell
{
	int	last_exit_status;
	char	**env;
		
} t_shell;

//init and tokenize
char	**tokenize_input(char *input);
void execute_command(char **tokens, t_shell *shell);
char	*get_path(char *cmd, char **env);
char	*get_env(char *key, char **env);
char	*handle_quotes(const char *input, int *index, char quote_type);

//utils
void	ft_free_tab(char **tab);

//env
char	*expand_variables(char *input, char **env);
char	*expand_exit_status(char *input, t_shell *shell);
void	builtin_env(char **env);
void heredoc(char *delimiter);

#endif