/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 19:48:21 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

pid_t	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_panic("fork", 1);
	return (pid);
}

int	count_number_of_commands(t_cmd *cmd)
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
	if (minishell->fork_cmd)
	{
		i = count_number_of_commands(minishell->fork_cmd);
		while (i > 0)
		{
			if (waitpid(0, &status, 0) == last_pid)
				minishell->exit_status = WEXITSTATUS(status);
			i--;
		}
	}
	else if (last_pid != 0)
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
