/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/01 20:00:48 by gahmed           ###   ########.fr       */
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

extern int	g_signal;

# define SUCCESS	0
# define FAIL		1
# define MAX_TOKENS 100

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

typedef struct s_shell
{
	t_dlist	*denv;
	int		exit_code;
	char	*old_pwd;
	char	**env;
	int		input_fd;
	int		fd[2];
	int		heredoc_fd;
	int		is_piped;
}			t_shell;

/* builtin_1 */
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_shell *minishell, int export_flag);
void	update_unset(t_shell *minishell, char *var);
int		ft_unset(t_shell *minishell, char **args);

/* builtin_2 */
void	update_env(t_shell *minishell, char *var);
int		ft_export(t_shell *minishell, char **custom_env);
void	update_directory(t_shell *minishell);
int		ft_cd(t_shell *minishell, char **args);
int		ft_exit(t_shell *minishell, char *args);

/* builtin_utils */
int		is_valid_var(char *var);
int		is_builtin(char *args);
int		execute_builtin(char **tokens, t_shell *minishell);

/* env_define */
char	*get_env(char *key, char **env);
char	*env_str(char *key, t_shell *shell);
char	*get_value(char *input, int *i, t_shell *shell);
char	*ms_strjoin(char *s1, char *s2);
char	*expand_variables(char *inputtt, t_shell *shell);

/* execution */
char	*handle_quotes(const char *input, int *index, char quote_type);
char	*get_next_token(char *input, int *i);
char	**tokenize_input(char *input);
void	execute_command(char **tokens, t_shell *shell);
void	run_command_in_child(char **tokens, t_shell *shell);
void	process_input(t_shell *shell, char *input);

/* signal */
void	signal_for_termination(int sig);
void	signal_handler(void);

/* utils_1 */
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
t_dlist	*convert_env_to_list(char **env);
void	ft_free_dlist(t_dlist *env);
void	ft_free_tab(char **tab);

/* utils_2 */
char	*ft_strndup(const char *src, size_t n);
char	*get_path(char *cmd, char **env);
int		ft_execvp(char *cmd, char **args, char **env);

/* redirection */
int		input_redirection(char **tokens, int *i);
int		output_redirection(char **tokens, int *i, int append);
int		handle_heredoc(char *delimiter, int is_piped);
int		handle_redirections(char **tokens);
void	execute_redirection(char **tokens, t_shell *shell);

/* pipes */
void	execute_piped_commands(char **commands, t_shell *shell);
char	**split_pipes(char *input);
void	execute_child_process(char **tokens, t_shell *shell, int has_cmd);
void	execute_parent_process(t_shell *shell, int has_cmd);

#endif