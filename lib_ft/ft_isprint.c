/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:16:11 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:06:37 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is printable.
 *
 * The function tests whether the input character `c` is a printable character,
 * meaning it is a character with a value between 32 and 126 inclusive.
 * This includes letters, digits, punctuation, and space.
 *
 * @param c The character to be checked, passed as an integer. The value of
 *          `c` should be representable as an unsigned char or EOF.
 *
 * @return Non-zero (true) if `c` is a printable character,
 *	and 0 (false) otherwise.
 *
 * @note This function behaves similarly to the standard `isprint` function
 *       in the C library,
 *	which checks for the range of printable ASCII characters.
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}
