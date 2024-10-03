/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:45:47 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:37:48 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies the string from the source to the destination with size limit.
 *
 * The function copies up to `size - 1` characters from the string `src` to 
 * `dst`, ensuring that `dst` is null-terminated. If `size` is less than or 
 * equal to 0, the function will not copy any characters and will return 
 * the length of `src`.
 *
 * @param dst A pointer to the destination string where `src` will be copied. 
 *            It must be large enough to hold the resulting string and the 
 *            null terminator.
 * @param src A pointer to the source string that will be copied to `dst`.
 * @param size The size of the buffer allocated for `dst`, which limits the 
 *             number of characters to copy from `src`.
 *
 * @return The total length of the string that would have been copied, which 
 *         is the length of `src`. If `size` is less than or equal to 0, 
 *         it will return the length of `src` without copying any characters.
 *
 * @note If `dst` is NULL or `src` is NULL, the function returns 0 without 
 *       performing any operations.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	local_size;

	if (!dst || !src)
		return (0);
	local_size = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (src[local_size] != '\0' && local_size < size - 1)
	{
		dst[local_size] = src[local_size];
		local_size++;
	}
	dst[local_size] = '\0';
	return (ft_strlen(src));
}
