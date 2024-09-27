/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/27 21:45:12 by gbuczyns         ###   ########.fr       */
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
	minishell->commands = (t_cmd **)calloc(sizeof(t_cmd *) * (pipe_count + 2),
			1);
	if (minishell->commands == NULL)
		panic("malloc");
	minishell->commands[pipe_count + 1] = NULL;
}

int	is_redirect(char *str)
{
	if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 || ft_strcmp(str,
			">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	is_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

int	get_token(char **ps)
{
	ft_skip_whitespace(ps);
	if (!strncmp(*ps, "<<", 2))
	{
		*ps += 2;
		return ('-');
	}
	else if (!strncmp(*ps, ">>", 2))
	{
		*ps += 2;
		return ('+');
	}
	else if (!strncmp(*ps, ">", 1))
	{
		*ps += 1;
		return ('>');
	}
	else if (!strncmp(*ps, "<", 1))
	{
		*ps += 1;
		return ('<');
	}
	else if (!strncmp(*ps, "|", 1))
	{
		*ps += 1;
		return ('|');
	}
	else
		return ('a');
}

void	parsecmd(t_data *minishell)
{
	int		i;
	t_cmd	*exec_cmd;
	t_cmd	*red_cmd;
	t_cmd	*current;
	char	*es;
	char	*ps;
	int		token;

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
			red_cmd = parseredirs(token, &ps, minishell);
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
				current->sub_cmd = exec_cmd;
			else
			{
				minishell->commands[i] = exec_cmd;
				minishell->number_of_commands++;
			}
			// red_cmd = NULL;
			i++;
		}
	}
	if (!current)
	{
		minishell->commands[i] = exec_cmd;
		minishell->number_of_commands++;
	}
}

t_cmd	*parseexec(char *str, t_cmd *exec_cmd)
{
	char	**argv;

	argv = exec_cmd->argv;
	exec_cmd->argv = ft_append_argv(argv, str);
	free(str);
	str = NULL;
	// exec_cmd->argv = remove_argv_quotes(argv); //remove in str
	return (exec_cmd);
}

/*
	if (ret_cmd->argv[1] != NULL)
		printf("argv[0]: %s\n argv[1]: %s\n", ret_cmd->argv[0],
			ret_cmd->argv[1]); */
t_cmd	*parseredirs(int tok, char **ps, t_data *minishell)
{
	t_cmd	*ret_cmd;
	char	*file;

	ret_cmd = NULL;
	file = NULL;
	file = get_word(ps);
	if (file == NULL)
		panic("missing file for redirection");
	if (tok == '<')
		ret_cmd = inputcmd(file, O_RDONLY, minishell);
	else if (tok == '>')
		ret_cmd = redircmd(file, O_CREAT | O_WRONLY | O_TRUNC, 1);
	else if (tok == '+')
		ret_cmd = redircmd(file, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (tok == '-')
		ret_cmd = here_doc_cmd(file);
	return (ret_cmd);
}
