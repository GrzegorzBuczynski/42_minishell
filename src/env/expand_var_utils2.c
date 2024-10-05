/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:42:35 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/05 23:50:12 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_for_spaces(char *input, int *length, int *i, bool is_in_quotes)
{
	if (*i > 0 && input[*i] == '|' && input[*i - 1] != ' ' && !is_in_quotes)
		(*length)++;
	if (input[*i] == '|' && input[*i + 1] != ' ' && input[*i + 1] != '\0'
		&& !is_in_quotes)
		(*length)++;
	if (input[*i] == '<' || input[*i] == '>')
		(*length) += 2;
	(*length) += 2;
	(*i)++;
}

char	*ft_strchrs_mf(const char *str, const char *c)
{
	char	*ptr;
	char	*chrs;

	ptr = (char *)str;
	while (*ptr)
	{
		chrs = (char *)c;
		while (*chrs)
		{
			if (*ptr == *chrs)
				return (ptr);
			chrs++;
		}
		ptr++;
	}
	if (*ptr == '\0')
		return (ptr);
	return (NULL);
}

char	*get_var_name(char *input, int *i)
{
	char	*name;
	char	*chrptr;

	if (!input || !i)
		return (NULL);
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	chrptr = input + *i;
	name = ft_strndup(chrptr, ft_strchrs_mf(chrptr, " \"\'/:.,=+") - chrptr);
	if (!name)
		return (NULL);
	*i += ft_strlen(name);
	return (name);
}

bool	toggle_quotes_state(bool is_in_quotes, char current_char)
{
	if (current_char == '\'')
		is_in_quotes = !is_in_quotes;
	return (is_in_quotes);
}

int	handle_variable_expansion(char *input, int *i, t_data *minishell,
		int *length)
{
	char	*name;

	(*i)++;
	name = get_var_name(input, i);
	if (!name)
		return (ERROR);
	if (*name == '?')
		*length += ft_strlen(ft_itoa(minishell->exit_status));
	else
		*length += ft_strlen(ft_get_var_value(name, minishell)) + 1;
	// free(name);
	return (1);
}
