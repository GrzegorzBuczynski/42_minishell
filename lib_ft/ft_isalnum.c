/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:22:20 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 18:58:51 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is alphanumeric.
 *
 * The function tests whether the input character `c` is alphanumeric,
 * meaning it is either an alphabetic letter (`a-z`, `A-Z`) or a digit (`0-9`).
 *
 * @param c The character to be checked, passed as an integer. The value of
 *          `c` must be representable as an unsigned char or be equal to EOF.
 *
 * @return Non-zero (true) if `c` is alphanumeric, and 0 (false) otherwise.
 *
 * @note This function behaves similarly to the standard `isalnum` function
 *       in the C library,
 *	leveraging the helper functions `ft_isalpha` and `ft_isdigit`.
 *
 * @warning Ensure that the value of `c` is within the valid range of
 *          `unsigned char` or equal to EOF to avoid undefined behavior.
 */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
