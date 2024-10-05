/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 22:20:52 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ------------------------------TO DO------------------------------
// 1) Validate input (quotes etc)
// 2) momory leaks
// 3) exit codes
// 4) move opening files to parsing
// 5) change commands to list

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	reset_minishell(t_data *minishell)
{
	minishell->input = NULL;
	minishell->pipe_argv = NULL;
	minishell->number_of_commands = 0;
	minishell->commands = NULL;
	minishell->exec_cmd = NULL;
	minishell->redir_cmd = NULL;
	minishell->fork_cmd = NULL;
}

void	minishell_loop(t_data *minishell)
{
	while (1)
	{
		minishell->input = gc_collector(readline(PROMPT), false, 1);
		// minishell->input = gc_collector(get_next_line(STDIN_FILENO), false, 1);
		if (minishell->input == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			gc_free((void *)1);
			gc_free((void *)1);
			gc_free((void *)1);

			exit(0);
		}
		if (minishell->input)
			add_history(minishell->input);
		minishell->input = replace_var(minishell->input, minishell);
		if (!is_input_valid(minishell->input))
		{
			// free(minishell->input);
			minishell->exit_status = 0;
			set_last_exit_code(minishell);
			continue ;
		}
		parsecmd(minishell);
		execute(minishell);
		gc_free((void *)2);
		gc_free((void *)2);
		gc_free((void *)2);
		set_last_exit_code(minishell);
		reset_minishell(minishell);
	}
}

void	init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
	tcgetattr(STDIN_FILENO, &minishell->terminal);
	minishell->number_of_commands = 0;
	minishell->exit_status = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	*minishell;

	(void)argc;
	(void)argv;
	(void)env;
	minishell = (t_data *)gc_calloc(sizeof(t_data), 1);
	signal(SIGINT, handle_sigint);
	init_minishell(minishell, env);
	init_environment(&(minishell->envlist), minishell->envir);
	minishell_loop(minishell);
	return (0);
}
