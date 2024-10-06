/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/06 15:48:10 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Skips leading whitespace characters in a string.
 *
 * This function takes a pointer to a string and advances the pointer
 * past any whitespace characters, including space, tab, carriage return,
 * newline, and vertical tab. It modifies the pointer to point to the
 * first non-whitespace character in the string.
 *
 * @param s A pointer to a pointer to the string to be processed.
 *          This pointer will be modified to point to the first non-whitespace
 *          character.
 *
 * @note If the input string is NULL or empty, the function will have no effect.
 */
void	ft_skip_whitespace(char **s)
{
	while (*s && **s && ft_strchr(" \t\r\n\v", **s))
		(*s)++;
}
