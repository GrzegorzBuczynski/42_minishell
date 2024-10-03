/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:52:49 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:39:54 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates a string up to a specified number of characters.
 *
 * This function allocates memory for a new string and copies up to `n` 
 * characters from the string pointed to by `s` into the newly allocated 
 * string. If the length of `s` is less than `n`, the entire string is 
 * duplicated, and the new string is null-terminated.
 *
 * @param s A pointer to the source string to be duplicated.
 * @param n The maximum number of characters to copy from `s`.
 *
 * @return A pointer to the newly allocated string on success, or NULL if 
 *         memory allocation fails.
 *
 * @note If `s` is NULL, the behavior is undefined.
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*newstr;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
