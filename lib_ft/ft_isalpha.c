/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:02:04 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:04:55 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is alphabetic.
 *
 * The function tests whether the input character `c` is an alphabetic letter,
 * either lowercase (`a-z`) or uppercase (`A-Z`).
 *
 * @param c The character to be checked, passed as an integer. The value of
 *          `c` must be representable as an unsigned char or be equal to EOF.
 *
 * @return Non-zero (true) if `c` is an alphabetic character,
 *	and 0 (false) otherwise.
 *
 * @note This function behaves similarly to the standard `isalpha` function
 *       in the C library, checking for both uppercase and lowercase letters.
 *
 * @warning Ensure that the value of `c` is within the valid range of
 *          `unsigned char` or equal to EOF to avoid undefined behavior.
 */
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
