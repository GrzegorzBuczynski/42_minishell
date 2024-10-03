/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:02:04 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:41:38 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts an uppercase letter to lowercase.
 *
 * This function takes an integer `c` representing a character 
 * and converts it to its lowercase equivalent if it is an 
 * uppercase letter. If `c` is not an uppercase letter, it 
 * returns `c` unchanged.
 *
 * @param c The character to be converted, represented as an 
 *          integer (typically a character from the ASCII set).
 *
 * @return The lowercase equivalent of the character if it 
 *         is an uppercase letter; otherwise, it returns the 
 *         original character.
 *
 * @note If `c` is not within the ASCII range for uppercase letters, 
 *       the function will return the character unchanged.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
