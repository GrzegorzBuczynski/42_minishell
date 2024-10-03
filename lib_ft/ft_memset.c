/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:30:40 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sets a block of memory to a specified value.
 *
 * The function fills the first `n` bytes of the memory area pointed to by 
 * `s` with the constant byte value `c`. This is commonly used to initialize 
 * memory or to clear a memory block.
 *
 * @param s A pointer to the memory area to be set.
 * @param c The value to set, which is converted to an unsigned char.
 * @param n The number of bytes to set to the specified value.
 * 
 * @return A pointer to the memory area `s`.
 * 
 * @note The function does not check for overlapping memory areas, as it is 
 *       intended to write to the specified memory area directly.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
