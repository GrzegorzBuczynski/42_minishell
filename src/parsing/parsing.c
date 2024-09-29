/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 21:12:51 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_exec(char **ps, t_data *minishell)
{
	ft_skip_whitespace(ps);
	if (!is_redirection(*ps) && !is_pipe(*ps))
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

	ft_skip_whitespace(ps);
	if (is_redirection(*ps))
	{
		ret_cmd = get_redir_cmd(ps, minishell);
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

void	parse_pipe(char **ps, t_data *minishell)
{
	t_cmd	*current;

	ft_skip_whitespace(ps);
	if (is_pipe(*ps))
	{
		if (minishell->pipe_cmd == NULL)
			minishell->pipe_cmd = ft_init_cmd(PIPE);
		current = minishell->pipe_cmd;
		while (current->sub_cmd)
			current = current->sub_cmd;
		current->exec_cmd = minishell->exec_cmd;
		current->redir_cmd = minishell->redir_cmd;
		minishell->exec_cmd = NULL;
		minishell->redir_cmd = NULL;
	}
}

void	setup_fork(t_data *minishell)
{
	t_cmd	*current;

	if (minishell->pipe_cmd)
	{
		current = minishell->pipe_cmd;
		while (current->sub_cmd)
			current = current->sub_cmd;
		current->sub_cmd = ft_init_cmd(PIPE);
		current = current->sub_cmd;
		current->exec_cmd = minishell->exec_cmd;
		current->redir_cmd = minishell->redir_cmd;
		minishell->exec_cmd = NULL;
		minishell->redir_cmd = NULL;
	}
}

void	parsecmd(t_data *minishell)
{
	char	*es;
	char	*ps;

	ps = minishell->input;
	es = minishell->input + ft_strlen(minishell->input);
	while (ps <= es && *ps)
	{
		parse_exec(&ps, minishell);
		parse_redir(&ps, minishell);
		parse_pipe(&ps, minishell);
	}
	setup_fork(minishell);
}

// void	alloc_mem_for_commands(t_data *minishell)
// {
// 	char	*input;
// 	int		pipe_count;

// 	pipe_count = 0;
// 	input = minishell->input;
// 	while (*input)
// 	{
// 		if (*input == '|')
// 			pipe_count++;
// 		input++;
// 	}
// 	minishell->commands = (t_cmd **)calloc(sizeof(t_cmd *) * (pipe_count + 2),
// 			1);
// 	if (minishell->commands == NULL)
// 		panic("malloc");
// 	minishell->commands[pipe_count + 1] = NULL;
// }

// int	is_redirect(char *str)
// {
// 	if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 || ft_strcmp(str,
// 			">>") == 0 || ft_strcmp(str, "<<") == 0)
// 		return (1);
// 	return (0);
// }

// int	is_pipe(char *str)
// {
// 	if (ft_strcmp(str, "|") == 0)
// 		return (1);
// 	return (0);
// }

// void	parsecmd(t_data *minishell)
// {
// 	char	*es;
// 	char	*ps;

// 	ps = minishell->input;
// 	es = minishell->input + ft_strlen(minishell->input);
// 	while (ps <= es && *ps)
// 	{
// 		// state = parse_block(&ps, state, minishell);
// 		parse_exec(&ps, minishell);
// 		parse_redir(&ps, minishell);
// 		parse_pipe(&ps,  minishell);
// 	}
// }

/* void	parsecmd(t_data *minishell)
{
	int		i;
	t_cmd	*exec_cmd;
	t_cmd	*red_cmd;
	t_cmd	*current;
	char	*es;
	char	*ps;
	int		token;
	char	**argv;

	i = 0;
	exec_cmd = ft_init_cmd(EXEC);
	current = NULL;
	red_cmd = NULL;
	ps = minishell->input;
	es = minishell->input + ft_strlen(minishell->input);
	while (ps <= es && *ps)
	{
		token = get_token(&ps);
		if (token == 'a')
		{
			parseexec(get_string(&ps), exec_cmd);
		}
		else if (token == '<' || token == '>' || token == '+' || token == '-')
		{
			red_cmd = get_redir_cmd(token, &ps, minishell);
			if (!current)
			{
				current = red_cmd;
				minishell->commands[i] = red_cmd;
				minishell->number_of_commands++;
				red_cmd = NULL;
			}
			else
			{
				current->sub_cmd = red_cmd;
				current = red_cmd;
				red_cmd = NULL;
			}
		}
		else if (token == '|')
		{
			if (current)
			{
				exec_cmd->argv = remove_argv_quotes(exec_cmd->argv);
				current->sub_cmd = exec_cmd;
			}
			else
			{
				exec_cmd->argv = remove_argv_quotes(exec_cmd->argv);
				minishell->commands[i] = exec_cmd;
				minishell->number_of_commands++;
				exec_cmd = ft_init_cmd(EXEC);
			}
			// red_cmd = NULL;
			i++;
		}
	}
	if (!current)
	{
		exec_cmd->argv = remove_argv_quotes(exec_cmd->argv);
		minishell->commands[i] = exec_cmd;
		minishell->number_of_commands++;
	}
} */
// t_cmd	*parseexec(char *str, t_cmd *exec_cmd)
// {
// 	argv = exec_cmd->argv;
// 	exec_cmd->argv = ft_append_argv(argv, str);
// 	free(str);
// 	str = NULL;
// 	// exec_cmd->argv = remove_argv_quotes(argv); //remove in str
// 	return (exec_cmd);
// }

// /*
// 	if (ret_cmd->argv[1] != NULL)
// 		printf("argv[0]: %s\n argv[1]: %s\n", ret_cmd->argv[0],
// 			ret_cmd->argv[1]); */
