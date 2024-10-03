/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 18:56:16 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sets a block of memory to zero.
 *
 * The function writes `n` zero bytes to the memory area pointed to by `s`.
 * It is often used to clear or reset memory buffers.
 *
 * @param s A pointer to the memory area to be zeroed.
 * @param n The number of bytes to set to zero.
 * 
 * @return None.
 * 
 * @note This function is typically used to initialize or reset buffers by 
 *       filling them with zero bytes (`'\0'`). It behaves similarly to 
 *       the standard `bzero` function.
 * 
 * @warning The behavior is undefined if `s` is `NULL` or if `n` is greater 
 *          than the size of the allocated memory for `s`.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
