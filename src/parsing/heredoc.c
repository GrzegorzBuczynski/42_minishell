/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:03:45 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 23:58:42 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_matching_token(char *line, char *token)
{
	if (strcmp(line, token) == 0)
		return (1);
	return (0);
}

void	take_input(t_cmd *cmd, char *token)
{
	char	*line;

	init_cmd_argv(cmd);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (is_matching_token(line, token))
			break ;
		else
		{
			add_history(line);
			cmd->argv[0] = gc_collector(ft_strjoin(cmd->argv[0], line), false, 2);
			cmd->argv[0] = gc_collector(ft_strjoin(cmd->argv[0], "\n"), false, 2);
		}
	}
}

t_cmd	*here_doc_cmd(char *token)
{
	t_cmd	*cmd;

	cmd = ft_init_cmd(HERE_DOC);
	cmd->sub_cmd = NULL;
	take_input(cmd, token);
	return (cmd);
}

void	do_here_doc(t_cmd *cmd, t_data *minishell)
{
	int	p[2];

	pipe(p);
	if (fork1() == 0)
	{
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		printf("%s", cmd->argv[0]);
		exit(0);
	}
	if (fork1() == 0)
	{
		dup2(p[0], 0);
		close(p[1]);
		close(p[0]);
		if (cmd->sub_cmd)
			runcmd(cmd->sub_cmd, minishell);
		else
			runcmd(cmd->exec_cmd, minishell);
		exit(0);
	}
	close(p[1]);
	close(p[0]);
	wait(0);
	wait(0);
	exit(0);
}
