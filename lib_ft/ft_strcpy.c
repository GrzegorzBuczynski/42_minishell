/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:58:30 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 19:36:05 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies a string from source to destination.
 *
 * The function copies the string pointed to by `src` (including the 
 * null terminator) into the buffer pointed to by `dest`. The function 
 * assumes that the destination buffer is large enough to hold the 
 * copied string.
 *
 * @param dest A pointer to the destination buffer where the string 
 *             will be copied. It must be a writable and sufficiently 
 *             large memory area.
 * @param src A pointer to the null-terminated string to be copied.
 * 
 * @return A pointer to the destination string `dest`.
 *
 * @note The behavior is undefined if `src` and `dest` overlap or if 
 *       `dest` is not large enough to hold the copied string. 
 *       Always ensure that `dest` has enough space to accommodate 
 *       the copied content.
 */
char	*ft_strcpy(char *dest, const char *src)
{
	char	*ret;

	ret = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ret);
}
