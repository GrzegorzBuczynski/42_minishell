/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:30:16 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Moves a block of memory from source to destination.
 *
 * The function copies `n` bytes from the memory area pointed to by `src` 
 * to the memory area pointed to by `dest`, handling potential overlap 
 * between the two memory areas. If the areas overlap, the copy is done 
 * in a manner that ensures the original data is preserved.
 *
 * @param dest A pointer to the destination memory area where the content 
 *             is to be moved.
 * @param src A pointer to the source memory area from which the content 
 *            is to be moved.
 * @param n The number of bytes to move from `src` to `dest`.
 * 
 * @return A pointer to the destination memory area `dest`.
 * 
 * @note If both `dest` and `src` are `NULL`, the function returns `NULL`. 
 *       The function handles overlapping regions correctly, ensuring data 
 *       integrity during the move operation.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = dest;
	ptr2 = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (ptr1 < ptr2)
		ft_memcpy(dest, src, n);
	else
	{
		i = n;
		while (i > 0)
		{
			ptr1[i - 1] = ptr2[i - 1];
			i--;
		}
	}
	return (dest);
}
