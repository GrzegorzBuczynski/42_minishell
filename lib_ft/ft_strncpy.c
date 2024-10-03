/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:30:12 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/03 20:27:18 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies a string up to a specified number of characters.
 *
 * This function copies up to `num` characters from the string pointed to by 
 * `src` to the string pointed to by `dest`. If the length of `src` is less 
 * than `num`, the remainder of `dest` is filled with null bytes ('\0').
 *
 * @param dest A pointer to the destination string where the content is to be 
 *             copied.
 * @param src A pointer to the source string to be copied.
 * @param num The maximum number of characters to copy from `src`.
 *
 * @return A pointer to the destination string `dest`.
 *
 * @note If `num` is less than or equal to 0, the behavior is undefined.
 *       If `src` is NULL, the behavior is also undefined.
 */
char	*ft_strncpy(char *dest, const char *src, int num)
{
	int	i;

	i = 0;
	while (i < num && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < num)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
