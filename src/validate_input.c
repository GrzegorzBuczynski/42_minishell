/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:15:21 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/02 20:34:24 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_replace_trailing_whitespace_with_null(char **input)
{
	int		i;
	char	*str;

	str = *input;
	i = strlen(*input) - 1;
	while (i >= 0 && ft_iswhitespace(str[i]))
	{
		str[i] = 0;
		i--;
	}
}

bool	is_non_whitespace_at_start(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_iswhitespace(input[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	has_invalid_trailing_chars(char *input)
{
	int		len;
	char	last;

	len = strlen(input);
	last = input[len - 1];
	return (last == '|' || last == '>' || last == '<');
}

bool	has_valid_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_input_valid(char *string)
{
	char	*input;

	input = string;
	if (!input || !is_non_whitespace_at_start(input))
		return (false);
	ft_replace_trailing_whitespace_with_null(&input);
	ft_skip_whitespace(&input);
	if (input[0] == '|' || has_invalid_trailing_chars(input))
		return (false);
	if (!has_valid_quotes(input))
		return (false);
	return (true);
}
