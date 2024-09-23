/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/23 19:33:49 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	alloc_mem_for_commands(t_data *minishell)
{
	char	*input;
	int		pipe_count;

	pipe_count = 0;
	input = minishell->input;
	while (*input)
	{
		if (*input == '|')
			pipe_count++;
		input++;
	}
	minishell->commands = (t_cmd **)malloc(sizeof(t_cmd *) * (pipe_count + 2));
	if (minishell->commands == NULL)
		panic("malloc");
	minishell->commands[pipe_count + 1] = NULL;
}

void	parsecmd(t_data *minishell)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*temp;
	char	*es;
	char	*ps;

	i = 0;
	cmd = NULL;
	temp = NULL;
	ps = minishell->input;
	es = minishell->input + ft_strlen(minishell->input);
	while (ps <= es)
	{
		cmd = parseredirs(cmd, &ps, es);
		if (cmd)
			cmd->sub_cmd = parseexec(&ps, minishell);
		else
		{
			cmd = parseexec(&ps, minishell);
			temp = parseredirs(cmd, &ps, es);
			if (temp)
				cmd = temp;
		}
		if (cmd)
		{
			// handle_quotes_dollar(cmd->argv, minishell);
			minishell->commands[i] = cmd;
			minishell->number_of_commands++;
		}
		peek(&ps, "|");
		ps++;
		i++;
	}
}

t_cmd	*parseexec(char **ps, t_data *minishell)
{
	t_cmd	*ret_cmd;

	ret_cmd = ft_init_cmd(EXEC);
	ret_cmd->argv = get_argv_for_single_cmd(ps);
	ret_cmd->argv = expand_variables(ret_cmd->argv, minishell);
	ret_cmd->argv = remove_argv_quotes(ret_cmd->argv);
	return (ret_cmd);
}

/*
	if (ret_cmd->argv[1] != NULL)
		printf("argv[0]: %s\n argv[1]: %s\n", ret_cmd->argv[0],
			ret_cmd->argv[1]); */
t_cmd	*parseredirs(t_cmd *sub_cmd, char **ps, char *es)
{
	int		tok;
	t_cmd	*ret_cmd;
	char	*file;

	ret_cmd = NULL;
	tok = 0;
	file = NULL;
	while (peek(ps, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		file = get_word(ps);
		if (file == NULL)
			panic("missing file for redirection");
		if (tok == '<')
			ret_cmd = redircmd(sub_cmd, file, O_RDONLY, 0);
		else if (tok == '>')
			ret_cmd = redircmd(sub_cmd, file, O_CREAT | O_WRONLY | O_TRUNC, 1);
		else if (tok == '+')
			ret_cmd = redircmd(sub_cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
			ret_cmd = here_doc_cmd(sub_cmd, file);
	}
	return (ret_cmd);
}
