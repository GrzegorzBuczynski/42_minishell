/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 19:03:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ft_init_cmd(int type)
{
	t_cmd	*cmd;

	cmd = gc_calloc(sizeof(*cmd), 1);
	if (!cmd)
		ft_panic("malloc", 1);
	cmd->type = type;
	return ((t_cmd *)cmd);
}

void	add_last_fork(t_data *minishell)
{
	t_cmd	*current;

	if (minishell->fork_cmd)
	{
		current = ft_init_cmd(FORK);
		current->exec_cmd = minishell->exec_cmd;
		current->redir_cmd = minishell->redir_cmd;
		minishell->exec_cmd = NULL;
		minishell->redir_cmd = NULL;
		append_fork_cmd(minishell, current);
	}
}

void	dequote_exec(t_data *minishell)
{
	t_cmd	*exec_cmd;

	exec_cmd = minishell->exec_cmd;
	if (exec_cmd)
		exec_cmd->argv = remove_argv_quotes(exec_cmd->argv);
}
