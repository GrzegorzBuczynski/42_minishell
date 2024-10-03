/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 18:57:37 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and zeroes memory for an array.
 *
 * The function allocates memory for an array of `nmemb` elements, each of 
 * `size` bytes, and initializes all bytes in the allocated memory to zero.
 * It behaves similarly to the standard `calloc` function.
 *
 * @param nmemb The number of elements to allocate.
 * @param size The size in bytes of each element.
 * 
 * @return A pointer to the allocated and zeroed memory. If the allocation 
 *         fails or if `nmemb` or `size` is zero, the function returns `NULL`.
 * 
 * @note If either `nmemb` or `size` is 0, the function allocates a minimal 
 *       amount of memory (1 byte) to ensure a valid memory address is returned.
 * 
 * @warning If the product of `nmemb` and `size` exceeds the maximum 
 *          size of an `int` (2147483647 bytes), the function returns `NULL` 
 *          to avoid overflow.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > 2147483647 / size)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
