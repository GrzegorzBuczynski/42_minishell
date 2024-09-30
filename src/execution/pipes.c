/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/30 20:40:32 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	create_pipes(t_cmd *cmd, t_data *minishell)
{
	int		forks;
	int		pipes;
	t_cmd	*current;

	forks = 0;
	pipes = 0;
	current = cmd;
	while (current)
	{
		forks++;
		current = current->sub_cmd;
	}
	minishell->pipe_argv = (int **)ft_calloc(sizeof(int *) * forks, 1);
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	while (pipes < forks - 1)
	{
		minishell->pipe_argv[pipes] = (int *)ft_calloc(2 * sizeof(int), 1);
		if (minishell->pipe_argv[pipes] == NULL)
			panic("malloc");
		if (pipe(minishell->pipe_argv[pipes]) == -1)
			panic("pipe");
		pipes++;
	}
}

int	execute(t_data *minishell)
{
	t_cmd	*cmd;
	pid_t	last_pid;

	if (minishell->fork_cmd)
	{
		cmd = minishell->fork_cmd;
		do_pipe(cmd, minishell);

	}
	else if (minishell->redir_cmd)
	{
		last_pid = fork1();
		if (last_pid == 0)
		{
			cmd = minishell->redir_cmd;
			runcmd(cmd, minishell);
		}
		wait_for_processes(minishell, last_pid);
	}
	else if (minishell->exec_cmd)
	{
		cmd = minishell->exec_cmd;
		if (is_builtin(cmd))
		{
			run_builtin_cmd(cmd->argv, minishell);
			return (0);
		}
		else
		{
			last_pid = fork1();
			if (last_pid == 0)
				runcmd(minishell->commands[0], minishell);
		}
		wait_for_processes(minishell, last_pid);
	}
	return (0);
}
