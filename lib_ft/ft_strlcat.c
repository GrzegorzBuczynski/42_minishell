/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:46:39 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends the source string to the destination string with size limit.
 *
 * The function appends the string `src` to the end of `dst`, ensuring that 
 * the total length of the resulting string does not exceed `size`. It also 
 * guarantees that `dst` is null-terminated. If `size` is less than or equal 
 * to the length of `dst`, the function does not modify `dst` and returns 
 * the sum of the lengths of `dst` and `src`.
 *
 * @param dst A pointer to the destination string to which `src` will be
 *			  appended. This string must be large enough to hold the result
 *            if `size` is greater than its current length.
 * @param src A pointer to the source string that will be appended to `dst`. 
 * @param size The size of the buffer allocated for `dst`. It determines the 
 *             maximum number of characters to append from `src` and ensures 
 *             the resulting string is null-terminated.
 *
 * @return The total length of the string that would have been created if 
 *         enough space had been available, which is the initial length of 
 *         `dst` plus the length of `src`. If `size` is less than or equal 
 *         to the length of `dst`, the return value will be the length of `src` 
 *         plus `size`.
 *
 * @note The caller must ensure that `dst` has enough space allocated to hold 
 *       the resulting string, including the null terminator.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len1;
	unsigned int	len2;

	i = 0;
	len1 = 0;
	len2 = 0;
	while (src[len1])
		len1++;
	while (dst[len2] && len2 < size)
		len2++;
	if (size <= len2)
		return (len1 + len2);
	while (src[i] && len2 + i < size - 1)
	{
		dst[len2 + i] = src[i];
		i++;
	}
	dst[len2 + i] = '\0';
	return (len1 + len2);
}
