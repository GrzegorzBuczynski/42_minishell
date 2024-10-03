/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:29:01 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies a block of memory from source to destination.
 *
 * The function copies `n` bytes from the memory area pointed to by `src` 
 * to the memory area pointed to by `dest`. The memory areas must not overlap; 
 * behavior is undefined if they do.
 *
 * @param dest A pointer to the destination memory area where the content 
 *             is to be copied.
 * @param src A pointer to the source memory area from which the content 
 *            is to be copied.
 * @param n The number of bytes to copy from `src` to `dest`.
 * 
 * @return A pointer to the destination memory area `dest`.
 * 
 * @note The function does not check for overlapping memory areas. If 
 *       the source and destination overlap, the behavior is undefined.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = dest;
	ptr2 = src;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (dest);
}
