/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:41:01 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 19:08:40 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is a whitespace character.
 *
 * The function tests whether the input character `c` is a whitespace
 * character. Whitespace characters include space, tab, newline,
 * carriage return, and vertical tab.
 *
 * @param c The character to be checked, passed as a `char`.
 *
 * @return Non-zero (true) if `c` is a whitespace character,
 *	and 0 (false) otherwise.
 *
 * @note This function checks for the following whitespace characters:
 *       - Space (`' '`)
 *       - Horizontal tab (`'\t'`)
 *       - Newline (`'\n'`)
 *       - Carriage return (`'\r'`)
 *       - Vertical tab (`'\v'`)
 */
int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}
