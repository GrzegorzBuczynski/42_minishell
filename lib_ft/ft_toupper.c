/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:02:04 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:41:55 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * This function takes an integer `c` representing a character 
 * and converts it to its uppercase equivalent if it is a 
 * lowercase letter. If `c` is not a lowercase letter, it 
 * returns `c` unchanged.
 *
 * @param c The character to be converted, represented as an 
 *          integer (typically a character from the ASCII set).
 *
 * @return The uppercase equivalent of the character if it 
 *         is a lowercase letter; otherwise, it returns the 
 *         original character.
 *
 * @note If `c` is not within the ASCII range for lowercase letters, 
 *       the function will return the character unchanged.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
