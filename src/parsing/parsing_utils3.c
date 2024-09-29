/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:30:14 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 19:32:42 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
	
char	*ft_substring(const char *start, const char *end)
{
	size_t	length;
	char	*result;

	length = end - start;
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strncpy(result, start, length);
	result[length] = '\0';
	return (result);
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

	length = 0;
	if (*ps == NULL || **ps == '\0')
		return (NULL);
	ft_skip_whitespace(ps);
	s = *ps;
	start = s;
	while (s && *s && !ft_iswhitespace(*s) ) //&& !is_redirection(*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (s && *s && *s != quote)
				s++;
		}
		if (*s == quote)
			s++;
		else
			s++;
	}
	length = s - start;
	ret = ft_strndup(start, length);
	*ps = s;
	return (ret);
}