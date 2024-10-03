/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:36:57 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:38:11 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a string.
 *
 * This function computes the length of the string `s`, not including the 
 * null terminator. If the input string is NULL, the function returns 0.
 *
 * @param s A pointer to the null-terminated string whose length is to be 
 *          computed. 
 *
 * @return The length of the string `s`, or 0 if `s` is NULL.
 *
 * @note This function does not count the null terminator in the returned 
 *       length.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
