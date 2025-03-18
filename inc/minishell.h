/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <mmonika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/18 15:40:40 by codespace        ###   ########.fr       */
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

typedef	struct	s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct	s_shell
{
	t_dlist	*denv;
	int		exit_code;
}			t_shell;

//init and tokenize
char	**tokenize_input(char *input);
void	execute_command(char **tokens, char **env, t_shell *minishell);
char	*get_path(char *cmd, char **env);
char	*get_env(char *key, char **env);

//utils
void	ft_free_tab(char **tab);

/* signal */
void	signal_for_termination(int sig);
void	signal_handler(void);

/* builtin */
int		ft_echo(char **args);
int		ft_pwd(void);
void	update_unset(t_shell *minishell, char *var);
int		ft_unset(t_shell *minishell, char **args);

/* builtin_2 */
void	update_env(t_shell *minishell, char *var);
int		ft_export(t_shell *minishell, char **custom_env);
int		ft_env(t_shell *minishell);

/* builtin_utils */
int 	is_valid_var(char *var);
int		is_builtin(char *args);
int		execute_builtin(char **tokens, t_shell *minishell);

/* utils */
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);

#endif