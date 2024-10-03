/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:40:39 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of a character in a string.
 *
 * This function scans the string `s` for the last occurrence of the 
 * character `c`. The search is performed from the end of the string 
 * towards the beginning.
 *
 * @param s The string to be searched.
 * @param c The character to locate in the string.
 *
 * @return A pointer to the last occurrence of `c` in `s`, or NULL if 
 *         the character is not found.
 *
 * @note If `c` is the null character ('\0'), the function returns a 
 *       pointer to the null terminator of the string.
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (unsigned char )c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
