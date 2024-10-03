/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:40:14 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates a substring in a string with a limit on the search length.
 *
 * This function searches for the first occurrence of the substring `little`
 * within the string `big`, considering only the first `len` characters of 
 * `big`. If `little` is an empty string, the function returns `big`.
 *
 * @param big The string in which to search for the substring.
 * @param little The substring to locate within `big`.
 * @param len The maximum number of characters to search in `big`.
 *
 * @return A pointer to the beginning of the located substring in `big` 
 *         if found, or NULL if `little` is not found or if `len` is zero.
 *
 * @note If `big` is NULL, the behavior is undefined. The search stops 
 *       when the end of `big` is reached or `len` characters have been checked.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0' && (j + i) < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
