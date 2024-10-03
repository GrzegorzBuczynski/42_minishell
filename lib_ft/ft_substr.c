/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:41:22 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a substring from a given string.
 *
 * This function allocates memory for a new string that contains
 * a portion of the original string `s`, starting from the index
 * `start` and extending for up to `len` characters.
 *
 * @param s The original string from which to create the substring.
 * @param start The starting index from which to extract the substring.
 * @param len The maximum length of the substring to be extracted.
 *
 * @return A newly allocated substring, or NULL if memory allocation 
 *         fails. If `start` is greater than the length of `s`, 
 *         an empty string is returned. If `len` exceeds the length 
 *         of the substring from `start`, it is adjusted accordingly.
 *
 * @note The resulting substring will always be null-terminated.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
