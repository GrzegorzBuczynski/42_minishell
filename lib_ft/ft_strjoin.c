/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:37:03 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Joins two strings into a new dynamically allocated string.
 *
 * The function concatenates the strings pointed to by `s1` and `s2`, 
 * allocating sufficient memory for the resulting string, including 
 * the null terminator. If either `s1` or `s2` is NULL, the function 
 * handles these cases by returning a duplicate of the non-NULL string 
 * or NULL if both are NULL.
 *
 * @param s1 A pointer to the first null-terminated string to be joined. 
 *            If NULL, `s2` will be returned as a duplicate.
 * @param s2 A pointer to the second null-terminated string to be joined. 
 *            If NULL, `s1` will be returned as a duplicate.
 *
 * @return A pointer to the newly allocated string that contains the 
 *         concatenated result of `s1` and `s2`, or NULL if memory 
 *         allocation fails or both `s1` and `s2` are NULL.
 *
 * @note The caller is responsible for freeing the memory allocated for 
 *       the resulting string to avoid memory leaks.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc(s1_len + s2_len + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, s1_len);
	ft_memcpy(joined + s1_len, s2, s2_len + 1);
	return (joined);
}
