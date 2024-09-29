/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 20:33:23 by gbuczyns         ###   ########.fr       */
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
	int		i;
	int		pipes;
	t_cmd	*current;

	i = 0;
	pipes = 0;
	current = cmd;
	while (current)
	{
		i++;
		current = current->sub_cmd;
	}
	minishell->pipe_argv = (int **)calloc(sizeof(int *) * i, 1);
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	while (pipes < i)
	{
		minishell->pipe_argv[i] = (int *)calloc(2 * sizeof(int), 1);
		if (minishell->pipe_argv[i] == NULL)
			panic("malloc");
		if (pipe(minishell->pipe_argv[i]) == -1)
			panic("pipe");
		pipes++;
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
