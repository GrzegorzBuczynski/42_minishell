/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/06 15:48:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a substring from a given range of characters.
 *
 * This function allocates memory for a new string and copies characters 
 * from the specified start pointer to the end pointer (exclusive). 
 * The length of the substring is determined by the difference between 
 * the two pointers. The resulting string is null-terminated.
 *
 * @param start A pointer to the beginning of the substring.
 * @param end A pointer to the end of the substring (exclusive).
 * 
 * @return A pointer to the newly allocated substring, or NULL if 
 *         memory allocation fails.
 */
char	*ft_substr2(const char *start, const char *end)
{
	size_t	length;
	char	*result;

	length = end - start;
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, start, length);
	result[length] = '\0';
	return (result);
}
