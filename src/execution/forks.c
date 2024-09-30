/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/30 20:16:43 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_pipes(int **pipe_argv, int i, t_cmd *cmd)
{
	if (i != 0)
		dup2(pipe_argv[i - 1][0], STDIN_FILENO);
	if (cmd->sub_cmd)
		dup2(pipe_argv[i][1], STDOUT_FILENO);
}

static void	close_pipes(int **pipe_argv)
{
	int	i;

	i = 0;
	while (pipe_argv[i])
	{
		close(pipe_argv[i][0]);
		close(pipe_argv[i][1]);
		i++;
	}
}

int	count_nuber_of_commands(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->sub_cmd;
	}
	return (i);
}

void	wait_for_processes(t_data *minishell, pid_t last_pid)
{
	int	status;
	int	i;

	status = 0;
	if (minishell->pipe_cmd)
	{
		i = count_nuber_of_commands(minishell->pipe_cmd);
		while (i > 0)
		{
			if (waitpid(0, &status, 0) == last_pid)
				minishell->exit_status = WEXITSTATUS(status);
			i--;
		}
	}
	else if(last_pid != 0)
	{
		waitpid(0, &status, 0);
		minishell->exit_status = WEXITSTATUS(status);
		return ;
	}
}

int	fork_and_run_command(t_cmd *cmd, t_data *minishell, int i)
{
	int	pid;
	int	**pipe_argv;

	pipe_argv = minishell->pipe_argv;
	// cmd = minishell->commands[i];
	pid = fork();
	if (pid == 0)
	{
		setup_pipes(pipe_argv, i, cmd);
		close_pipes(pipe_argv);
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
	int		i;

	i = 0;
	current = cmd;
	last_pid = fork_and_run_command(current, minishell, i);
	current = current->sub_cmd;
	i++;
	while (current)
	{
		last_pid = fork_and_run_command(current, minishell, i);
		current = current->sub_cmd;
		i++;
	}
	close_pipes(minishell->pipe_argv);
	wait_for_processes(minishell, last_pid);
}
