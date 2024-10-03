/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:11:22 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:39:15 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares two strings up to a specified number of characters.
 *
 * This function compares the first `n` characters of the strings pointed to 
 * by `s1` and `s2`. It returns an integer less than, equal to, or greater 
 * than zero if the first `n` characters of `s1` are found to be 
 * lexicographically less than, to match, or be greater than those of `s2`.
 *
 * @param s1 A pointer to the first string to be compared.
 * @param s2 A pointer to the second string to be compared.
 * @param n The maximum number of characters to compare.
 *
 * @return An integer less than, equal to, or greater than zero if the 
 *         first `n` characters of `s1` are found to be less than, 
 *         to match, or be greater than those of `s2`. If `n` is zero, 
 *         the function returns 0.
 *
 * @note If `s1` and `s2` are both NULL, the behavior is undefined.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
