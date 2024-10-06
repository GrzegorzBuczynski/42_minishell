/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 19:07:07 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_with_pipes(t_data *minishell)
{
	if (minishell->fork_cmd)
	{
		create_pipes(minishell->fork_cmd, minishell);
		make_forks(minishell->fork_cmd, minishell);
		return (1);
	}
	return (0);
}

void	runcmd(t_cmd *cmd, t_data *minishell)
{
	if (cmd == 0)
		exit(1);
	if (cmd->type == 0)
		exit(1);
	if (cmd->type == EXEC)
		do_exec(cmd, minishell);
	else if (cmd->type == REDIR)
		do_redirect(cmd, minishell);
	else if (cmd->type == HERE_DOC)
		do_here_doc(cmd, minishell);
	else
		exit(1);
	return ;
}

int	exec_with_redirects(t_data *minishell)
{
	pid_t	last_pid;

	if (minishell->redir_cmd)
	{
		signal(SIGINT, sig_kill);
		signal(SIGQUIT, sig_kill);
		last_pid = fork1();
		if (last_pid == 0)
		{
			runcmd(minishell->redir_cmd, minishell);
			runcmd(minishell->exec_cmd, minishell);
		}
		wait_for_processes(minishell, last_pid);
		init_signals();
		return (1);
	}
	return (0);
}

int	exec_exec_cmd(t_data *minishell)
{
	pid_t	last_pid;
	t_cmd	*cmd;

	if (minishell->exec_cmd)
	{
		cmd = minishell->exec_cmd;
		if (is_builtin(cmd))
		{
			run_builtin_cmd(cmd->argv, minishell);
			return (1);
		}
		else
		{
			signal(SIGINT, sig_kill);
			signal(SIGQUIT, sig_kill);
			last_pid = fork1();
			if (last_pid == 0)
				runcmd(cmd, minishell);
		}
		wait_for_processes(minishell, last_pid);
		init_signals();
	}
	return (0);
}

int	execute(t_data *minishell)
{
	if (exec_with_pipes(minishell))
		return (0);
	else if (exec_with_redirects(minishell))
		return (0);
	else if (exec_exec_cmd(minishell))
		return (0);
	return (0);
}
