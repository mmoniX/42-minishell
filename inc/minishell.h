/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/13 17:02:08 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS	0
# define FAIL		1
# define MAX_TOKEN	100

extern int	g_signal;

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
void	ft_exit(t_shell *minishell, char *args);

/* builtin_utils */
int		is_valid_var(char *var);
int		is_builtin(char *args);
int		execute_custom_builtin(char **tokens, t_shell *minishell);
void	execute_builtins(char **tokens, t_shell *shell);

/* check */
int		is_redirection(char *token);
int		is_valid_token(char *token);
int		check_syntax_errors(char **args);
char	*handle_quotes(const char *input, int *index, char quote_type);
char	*handle_special_tokens(char *input, int *i);

/* env_define */
char	*get_denv(char *key, t_dlist *denv);
char	*env_str(char *key, t_shell *shell);
char	*get_value(char *input, int *i, t_shell *shell);
char	*expand_segment(char *input, int *i, t_shell *shell);
char	*expand_variables(char *inputtt, t_shell *shell);

/* execution */
char	*get_simple_token(char *input, int *i);
char	*get_next_token(char *input, int *i);
char	**tokenize_input(char *input, t_shell *shell);
void	single_fork(char **tokens, t_shell *shell);
void	execute_single_commands(char **tokens, t_shell *shell);

/* main.c */
void	init_shell(t_shell *shell, char **env);
void	process_input(t_shell *shell, char *input);

/* pipes */
char	**split_pipes(char *input);
void	execute_piped_commands(char **commands, t_shell *shell);
void	execute_child_process(char **tokens, t_shell *shell, int has_cmd);
void	execute_parent_process(t_shell *shell, int has_cmd);
void	handle_pipe_process(char **tokens, t_shell *shell, int next_command);

/* redirection */
int		input_redirection(char **tokens, int *i);
int		output_redirec(char **tokens, int *i, int append);
int		handle_heredoc(char *delimiter, int is_piped);
int		handle_heredoc_redirection(char **tokens, t_shell *shell);
int		handle_redirections(char **tokens, t_shell *shell);

/* signal */
void	signal_for_termination(int sig);
void	signal_handler(void);
int		count_pipes(const char *input);
int		is_pipe(char c, char *quote);

/* utils_1 */
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
t_dlist	*convert_env_to_list(char **env);
char	*ms_strjoin(char *s1, char *s2);
int		skip_empty_token(char **token);

/* utils_2 */
char	*ft_strndup(const char *src, size_t n);
char	*get_path(char *cmd, t_dlist *denv);
void	check_directory(char *cmd, t_shell *shell);
int		ft_execvp(char *cmd, char **args, t_shell *minishell);

/* utils_3 */
void	ft_free_dlist(t_dlist *env);
void	ft_free_tab(char **tab);
void	ft_free_token(char **token);
void	dup_close(int o_stdin, int o_stdout);
char	*malloc_protection(char *str);

#endif