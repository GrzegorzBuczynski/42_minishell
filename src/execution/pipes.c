/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/30 21:25:46 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	setup_pipes(int **pipe_argv, int i, t_cmd *cmd)
{
	if (i != 0)
		dup2(pipe_argv[i - 1][0], STDIN_FILENO);
	if (cmd->sub_cmd)
		dup2(pipe_argv[i][1], STDOUT_FILENO);
}

void	close_pipes(int **pipe_argv)
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

