/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/17 00:14:37 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib_ft/libft.h"
# include "cmd.h"
# include "parsing.h"
# include "tokens.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "MDshell > "
# define YES 1
# define NO 0
# define FERROR 0
# define FSUCCESS 1
# define PERROR -1
# define PSUCCESS 0

// DRBUG_FIELD
// DELETE ME befor release
//========================================================================================//
# include "../lib_ft_printf/ft_printf.h"
//========================================================================================//
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
	char			*input;
	int				**pipe_argv;
	char			*environment;
	char			**envir;
	int				*pids;
	int				exit_status;
	int				num_of_cmds;
	t_env			*envlist;
	t_cmd			**commands;
	struct termios	terminal;
}					t_data;

// Validate_input
bool				ft_input_is_valid(char *input_str);

void				minishell_loop(t_data *minishell);

t_env				*environment_new_node(char *key, char *value);
void				environment_new_node_end(t_env **head, char *key,
						char *value);
void				init_environment(t_env **environment, char **env);
void				environment_free_list(t_env *head);

void				environment_free_list(t_env *head);

void				minishell_free(t_data *minishell, int flag);

t_tokens			*convert_input_to_tokens(t_data *minishell);

// tester functions
void				print_environment(t_env *node);

// tokens
void				init_tokens(t_data *minishell);

//	new potential libft function
char				*ft_strncpy(char *dest, char *src, int num);
void				ft_skip_whitespace(char **s);
bool				ft_is_whitespace(char c);

t_command			*parse_tokens(t_tokens *tokens);

int					check_syntax(t_tokens *tokens);
int					md_cd(char *path, t_data *minishell);
void				ft_update_env_list(char *key, char *value, bool yes,
						t_data *minishell);
char				*ft_get_envlst_val(char *key, t_data *minishell);
void				*gc_collector(void *list, bool free);
void				ft_envlstadd_back(t_env *new, t_data *minishell);
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					peek(char **ps, char *es, char *toks);
void				panic(char *s);
int					gettoken(char **ps, char *es, char **q, char **eq);

// execution
t_cmd				*ft_init_exec_cmd(void);
t_cmd				*redircmd(t_cmd *subcmd, char *file, char *efile, int mode,
						int fd);
t_cmd				*pipecmd(t_cmd *left, t_cmd *right);
t_cmd				*listcmd(t_cmd *left, t_cmd *right);
t_cmd				*backcmd(t_cmd *subcmd);
int					runcmd(struct s_cmd *cmd, t_data *minishell);
void				parsecmd(t_data *minishell);
t_cmd				*parseline(char **ps, char *es);
t_cmd				*parsepipe(char **ps, char *es);
t_cmd				*parseexec(char **ps, char *es);
t_cmd				*parseblock(char **ps, char *es);
t_cmd				*parseredirs(t_cmd *cmd, char **ps, char *es);
pid_t				fork1(void);
void				do_exec(t_cmd *cmd, t_data *minishell);
void				do_list(t_cmd *cmd, t_data *minishell);
void				do_back(t_cmd *cmd, t_data *minishell);
int					is_builtin_done(char **argv, t_data *minishell);
void				ft_expand_dolar(char **argv, t_data *minishell);
void				do_redirect(t_cmd *cmd, t_data *minishell);
int					ft_echo(char **argv);
char				**get_key_and_value(char *argument);
int					ft_unset(char **argv, t_data *minishell);
int					ft_export(char **argv, t_data *minishell);
int					ft_pwd(char **argv);
t_cmd				*here_doc_cmd(t_cmd *subcmd, char *q, char *eq);
void				take_input(t_heredoc_cmd *cmd, char *token);
int					ft_exit(void);
void				handle_exec_error(const char *msg, const char *arg);
void				clean_up(char *binary_path, char **paths);
char				**retrieve_paths(void);
char				*find_executable_path(t_execcmd *ecmd, char **paths);
char				**environment_list_to_array(t_env *environment);
void				make_forks(t_data *minishell);
void				create_pipes(t_data *minishell);
void				run_with_pipes(t_data *minishell);
void				alloc_mem_for_commands(t_data *minishell);
void				free_global(t_data *minishell);

void				malloc_int_array(int **destination, int size);
int					do_clear(void);

#endif