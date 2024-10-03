/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_string_numeric.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 20:02:53 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a given string represents a numeric value.
 *
 * This function verifies whether the input string is a valid representation of
 * an integer. It considers optional leading '+' or '-' signs and ensures that
 * all other characters are digits. If the string contains any non-digit
 * characters, the function returns 0 (false); otherwise, it returns 1 (true).
 *
 * @param str A pointer to the input string to be checked.
 *
 * @return 
 * - 1 if the string represents a numeric value (including optional sign).
 * - 0 if the string does not represent a numeric value.
 *
 * @note An empty string or a string with only signs is considered non-numeric.
 *       The function does not handle overflow or invalid representations (e.g., 
 *       "123abc", "+-", etc.).
 */
int	ft_is_string_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
