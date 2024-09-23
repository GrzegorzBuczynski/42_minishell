/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/23 19:06:23 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_greater_than(char **s)
{
	int	ret;

	ret = '>';
	(*s)++;
	if (**s == '>')
	{
		ret = '+';
		(*s)++;
	}
	return (ret);
}

static int	handle_less_than(char **s, char **ps)
{
	int	ret;

	ret = '<';
	(*s)++;
	if (**s == '<')
	{
		ret = '-';
		(*s)++;
	}
	*ps = *s;
	return (ret);
}

static int	handle_normal_token(char **s, char *es, char **eq)
{
	advance_to_end_of_token(s, es);
	if (eq)
		*eq = *s;
	return ('a');
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	ft_skip_whitespace(&s);
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (0);
	if (peek(&s, "|();&"))
		s++;
	else if (*s == '>')
		ret = handle_greater_than(&s);
	else if (*s == '<')
		ret = handle_less_than(&s, ps);
	else
		ret = handle_normal_token(&s, es, eq);
	ft_skip_whitespace(&s);
	*ps = s;
	return (ret);
}

/*
** Function returns array of strings
** stops converting when it reaches "<>|)&;"
*/
char	**get_argv_for_single_cmd(char **ps)
{
	char	*str;
	char	**argv;

	argv = NULL;
	while (!peek(ps, "<>|)&;") && **ps != 0)
	{
		str = get_string(ps);
		argv = ft_append_argv(argv, str);
		free(str);
	}
	return (argv);
}

char	**get_argv_blocks_in_quote(char **ps)
{
	char	*str;
	char	**argv;

	// char	*temp;
	while (*ps && **ps)
	{
		str = get_string(ps);
		argv = ft_append_argv(argv, str);
		free(str);
	}
	return (argv);
}

// temp = copy_without_quotes(str);
// expand_variable(&str, minishell);