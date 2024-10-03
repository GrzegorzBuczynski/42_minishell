/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:16:11 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:05:38 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is an ASCII character.
 *
 * The function tests whether the input character `c` is a valid ASCII 
 * character, which is any character with a value between 0 and 127 inclusive.
 *
 * @param c The character to be checked, passed as an integer. The value of 
 *          `c` should be representable as an unsigned char or EOF.
 * 
 * @return Non-zero (true) if `c` is an ASCII character, and 0 (false) otherwise.
 * 
 * @note This function behaves similarly to the standard `isascii` function 
 *       in the C library, checking if the value is within the 7-bit ASCII range.
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
