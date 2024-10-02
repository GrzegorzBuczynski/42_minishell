/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:15:21 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/02 19:58:11 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	ft_replace__trailing_whitespace_with_null(char **input)
{
	int		i;
	char	*str;

	str = *input;
	i = strlen(*input) - 1;
	while (i >= 0 && ft_iswhitespace((*input)[i]))
	{
		str[i] = 0;
		i--;
	}
}

bool	is_input_valid(char *string)
{
	int		i;
	char	quote;
	char	last;
	int		len;
	char	*input;

	i = 0;
	input = string;
	if (!input)
		return (false);
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n'
			&& input[i] != '\v' && input[i] != '\f' && input[i] != '\r')
			break ;
		else
			return (false);
		i++;
	}
	ft_replace__trailing_whitespace_with_null(&input);
	len = strlen(input);
	last = input[len - 1];
	ft_skip_whitespace(&input);
	if (input[0] == '|' || last == '|' || last == '>' || last == '<')
		return (false);
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
