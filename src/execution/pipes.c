/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 19:52:36 by gbuczyns         ###   ########.fr       */
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

void	create_pipes(t_data *minishell)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = minishell->number_of_commands - 1;
	minishell->pipe_argv = (int **)malloc(sizeof(int *) * pipes);
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	while (i < pipes)
	{
		minishell->pipe_argv[i] = (int *)malloc(2 * sizeof(int));
		if (minishell->pipe_argv[i] == NULL)
			panic("malloc");
		if (pipe(minishell->pipe_argv[i]) == -1)
			panic("pipe");
		i++;
	}
}

int	execute(t_data *minishell)
{
	t_cmd	*cmd;

	if (minishell->pipe_cmd)
	{
		cmd = minishell->pipe_cmd;
		runcmd(cmd, minishell);
	}
	else if (minishell->redir_cmd)
	{
		cmd = minishell->redir_cmd;
		runcmd(cmd, minishell);
		cmd = minishell->exec_cmd;
		runcmd(cmd, minishell);
	}
	else if (minishell->exec_cmd)
	{
		cmd = minishell->exec_cmd;
		runcmd(cmd, minishell);
	}
	else
		perror("No command to execute");
}
