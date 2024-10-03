/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:22:20 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:06:05 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is a digit.
 *
 * The function tests whether the input character `c` is a decimal digit 
 * (i.e., a character between '0' and '9').
 *
 * @param c The character to be checked, passed as an integer. The value of 
 *          `c` should be representable as an unsigned char or EOF.
 * 
 * @return Non-zero (true) if `c` is a digit, and 0 (false) otherwise.
 * 
 * @note This function behaves similarly to the standard `isdigit` function 
 *       in the C library, checking if the value is between '0' and '9'.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
