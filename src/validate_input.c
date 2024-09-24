/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:15:21 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/24 18:46:43 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// >>, >, <<, < at the end of the strng
// | at the beginning and the end of the string
// unclosed quotes or double quotes
// if unclosed double quotes are within single quotes the input is correct
// if unclosed single quotes are within double quotes the input is correct
// everything except $ within double quotes is treated as string literal

bool	is_valid_input(const char *input)
{
	bool single_quote_open = false;
	bool double_quote_open = false;
	size_t len = strlen(input);

	// Check if input ends with valid redirection operator
	if (len >= 2 && (strcmp(input + len - 2, ">>") == 0 || strcmp(input + len
				- 2, "<<") == 0))
	{
		len -= 2; // Reduce length to check the rest of the input
	}
	else if (len >= 1 && (input[len - 1] == '>' || input[len - 1] == '<'))
	{
		len -= 1; // Reduce length to check the rest of the input
	}

	// Check if input starts and ends with pipe
	if (input[0] == '|')
	{
		if (len > 0 && input[len - 1] == '|')
		{
			len--; // Ignore the ending pipe
		}
		else
		{
			return (false);
				// Invalid if it starts with | but doesn't end with it
		}
	}

	// Iterate through the input string to check quotes
	for (size_t i = 0; i < len; i++)
	{
		if (input[i] == '\'')
		{
			single_quote_open = !single_quote_open;
				// Toggle single quote status
		}
		else if (input[i] == '\"')
		{
			double_quote_open = !double_quote_open;
				// Toggle double quote status
		}
	}

	// At the end, quotes must be closed or in acceptable open states
	if ((single_quote_open && !double_quote_open) || (double_quote_open
			&& !single_quote_open))
	{
		return (false); // One of the quotes is unclosed
	}

	return (true); // All conditions met
}