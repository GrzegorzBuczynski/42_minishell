/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 21:04:07 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_pipes(int **pipe_argv, int i, int commands)
{
	if (i != 0)
		dup2(pipe_argv[i - 1][0], STDIN_FILENO);
	if (i != commands - 1)
		dup2(pipe_argv[i][1], STDOUT_FILENO);
}

static void	close_pipes(int **pipe_argv, t_cmd *cmd)
{
	int		i;
	t_cmd	*current;

	current = cmd;
	i = 0;
	while (current->sub_cmd)
	{
		close(pipe_argv[i][0]);
		close(pipe_argv[i][1]);
		current = current->sub_cmd;
		i++;
	}
}

void	wait_for_processes(t_data *minishell, pid_t last_pid)
{
	int	status;
	int	i;

	status = 0;
	i = minishell->number_of_commands;
	while (i > 0)
	{
		if (waitpid(0, &status, 0) == last_pid)
			minishell->exit_status = WEXITSTATUS(status);
		i--;
	}
}

int	fork_and_run_command(t_cmd *cmd, t_data *minishell, int i)
{
	int		pid;
	int		**pipe_argv;
	int		commands;
	t_cmd	*current;

	current = cmd;
	pipe_argv = minishell->pipe_argv;
	commands = minishell->number_of_commands;
	// cmd = minishell->commands[i];
	pid = fork();
	if (pid == 0)
	{
		setup_pipes(pipe_argv, i, commands);
		close_pipes(pipe_argv, current);
		if (cmd->redir_cmd)
			runcmd(cmd->redir_cmd, minishell);
		runcmd(cmd->exec_cmd, minishell);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	make_forks(t_cmd *cmd, t_data *minishell)
{
	pid_t	last_pid;
	t_cmd	*current;
	int		**pipe_argv;
	int		i;

	i = 0;
	current = cmd;
	last_pid = fork_and_run_command(current, minishell, i);
	pipe_argv = minishell->pipe_argv;
	if (!(current->sub_cmd))
		close(pipe_argv[i][1]);
	if (i != 0)
		close(pipe_argv[i - 1][0]);
	i++;
	while (current->sub_cmd)
	{
		current = current->sub_cmd;
		last_pid = fork_and_run_command(current, minishell, i);
		if (!(current->sub_cmd))
			close(pipe_argv[i][1]);
		if (i != 0)
			close(pipe_argv[i - 1][0]);
		i++;
	}
	close_pipes(pipe_argv, cmd);
	wait_for_processes(minishell, last_pid);
}
