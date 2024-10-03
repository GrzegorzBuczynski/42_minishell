/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:35:23 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * The function searches for the first occurrence of the character `c` 
 * in the string `s`. The search includes the null terminator. 
 * If the character is found, a pointer to its location in the string 
 * is returned; otherwise, NULL is returned.
 *
 * @param s A pointer to the null-terminated string to be searched. 
 *          This string should not be NULL.
 * @param c The character to be located in the string. It is passed as 
 *          an integer, but it is interpreted as a character.
 * 
 * @return A pointer to the first occurrence of the character `c` in the 
 *         string `s`, or NULL if the character is not found. If `c` is 
 *         the null terminator, a pointer to the null terminator in `s` 
 *         is returned.
 *
 * @note The function does not perform any error checking on the input 
 *       string. If `s` is NULL, the behavior is undefined.
 */
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
