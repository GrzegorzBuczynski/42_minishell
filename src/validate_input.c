/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:15:21 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/25 16:28:57 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_input_valid(const char *input)
{
	int		i;
	char	quote;
	char	last;
	int		len;

	len = strlen(input);
	last = input[len - 1];
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

// int	main(void)
// {
// 	char *input = "t34rvwerv\"dsacrawcer\"sdfsdf 'r4af44'|";
// 	int	i;

// 	i = is_input_valid(input);
// 	printf("%d\n", i);
// 	return (0);
// }