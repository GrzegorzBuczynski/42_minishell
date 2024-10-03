/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:28:17 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of a character in a memory block.
 *
 * The function scans the memory area pointed to by `s` for the first occurrence 
 * of the character `c`, examining up to `n` bytes. If the character is found, 
 * a pointer to the matching byte is returned. If the character is not found 
 * within the given range, the function returns `NULL`.
 *
 * @param s A pointer to the memory block to be searched.
 * @param c The character to search for, passed as an `int` but treated as 
 *          an `unsigned char`.
 * @param n The number of bytes to be examined in the memory block.
 * 
 * @return A pointer to the first occurrence of `c` in the memory block, or 
 *         `NULL` if the character is not found within the specified range.
 * 
 * @note The function does not modify the memory block; it only reads from it.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*pos;
	size_t				i;

	pos = s;
	i = 0;
	while (i < n)
	{
		if (pos[i] == (unsigned char)c)
			return ((void *)(pos + i));
		i++;
	}
	return (0);
}
