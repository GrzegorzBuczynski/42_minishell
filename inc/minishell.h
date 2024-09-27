/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:40:11 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/27 20:33:21 by gbuczyns         ###   ########.fr       */
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
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "MDshell > "
# define YES 1
# define NO 0
# define true 1
# define false 0
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
int					peek(char **ps, char *toks);
void				panic(char *s);
int					gettoken(char **ps, char *es, char **q, char **eq);
char				*get_word(char **ps);

// execution
t_cmd				*ft_init_cmd(int type);
t_cmd				*redircmd(char *file, int mode, int fd);
t_cmd				*pipecmd(t_cmd *left, t_cmd *right);
t_cmd				*listcmd(t_cmd *left, t_cmd *right);
t_cmd				*backcmd(t_cmd *subcmd);
void				runcmd(struct s_cmd *cmd, t_data *minishell);
void				parsecmd(t_data *minishell);
t_cmd				*parseline(char **ps, char *es);
t_cmd				*parseblock(char **ps, char *es);
t_cmd				*parseredirs(int tok, char **ps, t_data *minishell);
t_cmd				*parseexec(char *str, t_cmd *exec_cmd);

pid_t				fork1(void);
void				do_exec(t_cmd *cmd, t_data *minishell);
void				do_list(t_cmd *cmd, t_data *minishell);
void				do_back(t_cmd *cmd, t_data *minishell);
int					run_builtin_cmd(char **argv, t_data *minishell);
void				ft_expand_dollar(char **argv, t_data *minishell);
void				do_redirect(t_cmd *cmd, t_data *minishell);
int					ft_echo(char **argv);
char				**get_key_and_value(char *argument);
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
char				*find_executable_path(t_cmd *ecmd, char **paths);
char				**environment_list_to_array(t_env *environment);
void				make_forks(t_data *minishell);
void				create_pipes(t_data *minishell);
int					execute(t_data *minishell);
void				alloc_mem_for_commands(t_data *minishell);
void				free_global(t_data *minishell);
char				*ft_substring(const char *start, const char *end);
char				**get_argv_for_single_cmd(char **ps);
void				advance_to_end_of_token(char **s, char *es);

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
void				handle_quotes_dollar(char **argv, t_data *minishell);
void				init_cmd_argv(t_cmd *cmd);

int					is_builtin(t_cmd *cmd);
char				*copy_without_quotes(char *s);
bool				ft_is_inside_quotes(char *stack, char *needle, char token1,
						char token2);
char				**get_argv_blocks_in_quote(char **ps);
char				**remove_argv_quotes(char **argv);
char				**expand_variables(char **argv, t_data *minishell);
bool				is_absolute_or_relative_path(const char *cmd);
char				*ft_strstr(const char *haystack, const char *needle);
char				*replace_var(char *input, t_data *minishell);
void				set_last_exit_code(t_data *minishell);
t_cmd				*inputcmd(char *file, int mode, t_data *minishell);
void				wait_for_processes(t_data *minishell, pid_t last_pid);

#endif