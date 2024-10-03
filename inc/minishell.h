/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:40:11 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:47:53 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib_ft/libft.h"
# include "cmd.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "MDshell > "
# define YES 1
# define NO 0
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define NOT_SET -1
# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
#  define EXIT_FAILURE -1
# endif

# define FILE_CONTROL_G 0

# ifndef FILE_CONTROL_G
#  define O_RDONLY 0
#  define O_WRONLY 1
#  define O_RDWR 2
#  define O_CREAT 64
#  define O_APPEND 1024
#  define O_TRUNC 512
# endif

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_llist
{
	void			*content;
	struct s_llist	*previous;
	struct s_llist	*next;
}					t_llist;

typedef struct s_data
{
	int				**pipe_argv;
	int				exit_status;
	int				number_of_commands;
	char			*input;
	char			*last_cmd;
	char			**envir;
	char			*environment;
	t_env			*envlist;
	t_cmd			**commands;
	struct termios	terminal;
	t_cmd			*redir_cmd;
	t_cmd			*exec_cmd;
	t_cmd			*fork_cmd;
	int				error;
}					t_data;

// Validate_input
bool				is_input_valid(char *input);

void				minishell_loop(t_data *minishell);

t_env				*environment_new_node(char *key, char *value);
void				environment_new_node_end(t_env **head, char *key,
						char *value);
void				init_environment(t_env **environment, char **env);
void				environment_free_list(t_env *head);

void				environment_free_list(t_env *head);

void				minishell_free(t_data *minishell, int flag);

// tester functions
void				print_environment(t_env *node);

//	new potential libft function
char				*ft_strncpy(char *dest, char *src, int num);
void				ft_skip_whitespace(char **s);
char				*get_string(char **ps);
int					md_cd(char **argv, t_data *minishell);
void				ft_update_env_list(char *key, char *value, bool yes,
						t_data *minishell);
char				*ft_get_var_value(char *key, t_data *minishell);
void				*gc_collector(void *list, bool free);
void				ft_envlstadd_back(t_env *new, t_data *minishell);
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					get_token(char **ps);

// execution
t_cmd				*ft_init_cmd(int type);
t_cmd				*redircmd(char *file, int mode, int fd);
t_cmd				*listcmd(t_cmd *left, t_cmd *right);
t_cmd				*backcmd(t_cmd *subcmd);
void				parsecmd(t_data *minishell);
int					is_redirection(char *s);
t_cmd				*get_redir_cmd(char **ps);
int					is_pipe(char *s);

pid_t				fork1(void);
void				runcmd(t_cmd *cmd, t_data *minishell);
void				do_exec(t_cmd *cmd, t_data *minishell);
int					run_builtin_cmd(char **argv, t_data *minishell);
void				do_redirect(t_cmd *cmd, t_data *minishell);
int					ft_echo(char **argv);
int					ft_unset(char **argv, t_data *minishell);
int					ft_export(char *argv, t_data *minishell);
int					ft_pwd(char **argv);
t_cmd				*here_doc_cmd(char *token);
void				do_here_doc(t_cmd *cmd, t_data *minishell);
void				take_input(t_cmd *cmd, char *token);
int					ft_exit(char **args);
void				handle_exec_error(const char *msg, const char *arg);
void				clean_up(char *binary_path, char **paths);
char				**retrieve_paths(void);
char				*find_executable_path(t_cmd *ecmd);
char				**environment_list_to_array(t_env *environment);
void				make_forks(t_cmd *cmd, t_data *minishell);
void				create_pipes(t_cmd *cmd, t_data *minishell);
int					execute(t_data *minishell);
// void				alloc_mem_for_commands(t_data *minishell);
void				free_global(t_data *minishell);
char				*ft_substring(const char *start, const char *end);
void				init_cmd_args(t_cmd *cmd);
void				add_argument(t_cmd *cmd, char *q, char *eq, int *argc);
void				print_environment_sorted(t_env *node);
void				sort_env_vars(t_env **env_array, size_t count);

void				print_sorted_env_vars(t_env **env_array, size_t count);
size_t				count_env_vars(t_env *node);
t_env				**collect_env_vars(t_env *node, size_t count);
void				sort_env_vars(t_env **env_array, size_t count);
void				do_redirect(t_cmd *cmd, t_data *minishell);
void				remove_quotess(char **str);
void				init_cmd_argv(t_cmd *cmd);

int					is_builtin(t_cmd *cmd);
char				**remove_argv_quotes(char **argv);
char				*replace_var(char *input, t_data *minishell);
void				set_last_exit_code(t_data *minishell);
t_cmd				*inputcmd(char *file);
void				wait_for_processes(t_data *minishell, pid_t last_pid);
int					exec_with_pipes(t_data *minishell);
char				*remove_quotes(char *s);
void				close_pipes(int **pipe_argv);
void				setup_pipes(int **pipe_argv, int i, t_cmd *cmd);
void				read_file_access(char *file);
int					check_file(char *path);
void				set_quotes(char *quotes, char word);
bool				do_copy_var(int quotes, char *input, int i);
int					replace_var_loop(char *input, t_data *minishell,
						char *result, int i);
int					add_space(int i, int quotes, char *input);
int					add_another_space(int i, int quotes, char *input);
int					copy_variable(char *name, t_data *minishell, int *j,
						char *result);
char				*get_var_name(char *input, int *i);
void				check_for_spaces(char *input, int *length, int *i,
						bool is_in_quotes);
void				free_syntax_error(t_data *minishell);
void				append_fork_cmd(t_data *minishell, t_cmd *ret_cmd);
void				dequote_exec(t_data *minishell);
void				add_last_fork(t_data *minishell);
void				rise_level(t_data *minishell);
bool				toggle_quotes_state(bool is_in_quotes, char current_char);
int					handle_variable_expansion(char *input, int *i,
						t_data *minishell, int *length);
#endif