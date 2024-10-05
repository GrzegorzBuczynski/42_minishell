/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:30:14 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 21:20:06 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*skip_quotes(char *s, int quote)
{
	while (*s && *s != quote)
		s++;
	if (*s == quote)
		s++;
	return (s);
}

/*
 * Returns a string from the input string.
 * The string can be a block or a word.
 * A block is a string between two quotes.
 * A word is a string between two whitespaces.
 */
char	*get_string(char **ps)
{
	char	*s;
	char	*ret;
	size_t	length;
	char	*start;
	int		quote;

	if (*ps == NULL || **ps == '\0')
		return (NULL);
	ft_skip_whitespace(ps);
	s = *ps;
	start = s;
	while (*s && !ft_iswhitespace(*s))
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s++;
			s = skip_quotes(s, quote);
		}
		else
			s++;
	}
	length = s - start;
	ret = gc_collector(ft_strndup(start, length), false, 1);
	*ps = s;
	return (ret);
}

void	free_syntax_error(t_data *minishell)
{
	if (minishell->error)
	{
		minishell->exit_status = 1;
		minishell->error = 0;
		minishell->exec_cmd = NULL;
		minishell->redir_cmd = NULL;
		minishell->fork_cmd = NULL;
	}
}
