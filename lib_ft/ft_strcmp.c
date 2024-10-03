/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:24:30 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 19:35:43 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares two strings lexicographically.
 *
 * The function compares the two strings `s1` and `s2` character by 
 * character. It continues comparing until a null terminator is 
 * encountered in either string or until a difference is found. 
 * The result is determined based on the difference between the 
 * first differing characters.
 *
 * @param s1 A pointer to the first string to be compared.
 * @param s2 A pointer to the second string to be compared.
 * 
 * @return An integer less than, equal to, or greater than zero, 
 *         depending on whether `s1` is less than, equal to, or 
 *         greater than `s2`.
 *         - A negative value indicates `s1` is less than `s2`.
 *         - Zero indicates `s1` is equal to `s2`.
 *         - A positive value indicates `s1` is greater than `s2`.
 *
 * @note The comparison is case-sensitive, and the function handles 
 *       characters as unsigned char values to avoid negative results 
 *       for characters with ASCII values greater than 127.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
