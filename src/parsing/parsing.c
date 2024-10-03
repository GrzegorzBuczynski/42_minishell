/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 20:18:05 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_exec(char **ps, t_data *minishell)
{
	ft_skip_whitespace(ps);
	if (!ft_isredirection(*ps) && !ft_ispipe(*ps))
	{
		if (minishell->exec_cmd == NULL)
			minishell->exec_cmd = ft_init_cmd(EXEC);
		minishell->exec_cmd->argv = ft_append_argv(minishell->exec_cmd->argv,
				get_string(ps));
	}
}

void	parse_redir(char **ps, t_data *minishell)
{
	t_cmd	*current;
	t_cmd	*ret_cmd;

	current = NULL;
	ret_cmd = NULL;
	ft_skip_whitespace(ps);
	if (ft_isredirection(*ps))
	{
		ret_cmd = get_redir_cmd(ps);
		if (minishell->redir_cmd == NULL)
			minishell->redir_cmd = ret_cmd;
		else
		{
			current = minishell->redir_cmd;
			while (current->sub_cmd)
				current = current->sub_cmd;
			current->sub_cmd = ret_cmd;
		}
	}
}

void	append_fork_cmd(t_data *minishell, t_cmd *ret_cmd)
{
	t_cmd	*current;

	if (minishell->fork_cmd == NULL)
	{
		minishell->fork_cmd = ret_cmd;
	}
	else
	{
		current = minishell->fork_cmd;
		while (current->sub_cmd)
			current = current->sub_cmd;
		current->sub_cmd = ret_cmd;
	}
}

void	parse_fork(char **ps, t_data *minishell)
{
	t_cmd	*ret_cmd;
	t_cmd	*exec_cmd;

	exec_cmd = minishell->exec_cmd;
	ft_skip_whitespace(ps);
	if (ft_ispipe(*ps))
	{
		*ps = *ps + 1;
		ret_cmd = ft_init_cmd(FORK);
		exec_cmd->argv = remove_argv_quotes(exec_cmd->argv);
		ret_cmd->redir_cmd = minishell->redir_cmd;
		ret_cmd->exec_cmd = minishell->exec_cmd;
		minishell->exec_cmd = NULL;
		minishell->redir_cmd = NULL;
		append_fork_cmd(minishell, ret_cmd);
	}
}

void	parsecmd(t_data *minishell)
{
	char	*ps;

	if (!minishell->input)
		return ;
	ps = minishell->input;
	while (ps && *ps && !minishell->error)
	{
		parse_exec(&ps, minishell);
		parse_redir(&ps, minishell);
		parse_fork(&ps, minishell);
	}
	free_syntax_error(minishell);
	dequote_exec(minishell);
	add_last_fork(minishell);
}
