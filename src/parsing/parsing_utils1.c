/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 19:11:41 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(char **s)
{
	ft_skip_whitespace(s);
	if (!strncmp(*s, "<<", 2))
		return ('-');
	else if (!strncmp(*s, ">>", 2))
		return ('+');
	else if (!strncmp(*s, ">", 1))
		return ('>');
	else if (!strncmp(*s, "<", 1))
		return ('<');
	return (0);
}

int	is_pipe(char **s)
{
	ft_skip_whitespace(s);
	if (!strncmp(*s, "|", 1))
	{
		*s += 1;
		return ('|');
	}
	return (0);
}

void	ft_skip_whitespace(char **s)
{
	while (*s && **s && ft_strchr(" \t\r\n\v", **s))
		(*s)++;
}

t_cmd	*get_redir_cmd(char **ps, t_data *minishell)
{
	t_cmd	*ret_cmd;
	char	*file;
	int		tok;

	tok = get_token(ps);
	ret_cmd = NULL;
	file = NULL;
	file = get_string(ps);
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


/*
** Function skip whitespaces and moves *ps pointer to the next
** character like in the tokens string.
** Returns 1 if the character is in the toks string, 0 otherwise.
*/
// int	peek(char **ps, char *toks)
// {
// 	char	*s;

// 	s = *ps;
// 	while (s && *s && strchr(" \t\r\n\v", *s))
// 		s++;
// 	*ps = s;
// 	return (*s && strchr(toks, *s));
// }



// void	advance_to_end_of_token(char **s, char *es)
// {
// 	while (*s < es && !strchr(" \t\r\n\v", **s) && !strchr("<|>&;()", **s))
// 		(*s)++;
// }

// char	*ft_substring(const char *start, const char *end)
// {
// 	size_t	length;
// 	char	*result;

// 	length = end - start;
// 	result = malloc(length + 1);
// 	if (result == NULL)
// 		return (NULL);
// 	strncpy(result, start, length);
// 	result[length] = '\0';
// 	return (result);
// }

// char	*get_block(char **ps)
// {
// 	char	*ret;
// 	char	*s;
// 	size_t	length;
// 	char	*start;
// 	char	quote;

// 	s = *ps;
// 	quote = *s;
// 	length = 0;
// 	start = s;
// 	s++;
// 	while (s && *s && *s != quote)
// 		s++;
// 	length = s - start + 1;
// 	ret = malloc(length + 1);
// 	if (ret == NULL)
// 		return (NULL);
// 	strncpy(ret, start, length);
// 	ret[length] = '\0';
// 	if (quote)
// 		s++;
// 	*ps = s;
// 	return (ret);
// }

// char	*get_word(char **ps)
// {
// 	char	*ret;
// 	char	*s;
// 	size_t	length;
// 	char	*start;

// 	ft_skip_whitespace(ps);
// 	s = *ps;
// 	length = 0;
// 	start = s;
// 	while (s && *s && !ft_iswhitespace(*s))
// 		s++;
// 	length = s - start;
// 	ret = malloc(length + 1);
// 	if (ret == NULL)
// 		return (NULL);
// 	strncpy(ret, start, length);
// 	ret[length] = '\0';
// 	*ps = s;
// 	return (ret);
// }

// /*
//  * Returns a string from the input string.
//  * The string can be a block or a word.
//  * A block is a string between two quotes.
//  * A word is a string between two whitespaces.
//  */
// char	*get_string(char **ps)
// {
// 	char	*s;
// 	char	*ret;
// 	size_t	length;
// 	char	*start;
// 	int		quote;

// 	length = 0;
// 	if (*ps == NULL || **ps == '\0')
// 		return (NULL);
// 	ft_skip_whitespace(ps);
// 	s = *ps;
// 	start = s;
// 	while (s && *s && !ft_iswhitespace(*s) ) //&& !is_redirection(*s)
// 	{
// 		if (*s == '\'' || *s == '\"')
// 		{
// 			quote = *s;
// 			s++;
// 			while (s && *s && *s != quote)
// 				s++;
// 		}
// 		if (*s == quote)
// 			s++;
// 		else
// 			s++;
// 	}
// 	length = s - start;
// 	ret = ft_strndup(start, length);
// 	*ps = s;
// 	return (ret);
// }