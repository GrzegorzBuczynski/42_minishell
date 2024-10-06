/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/06 15:47:50 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of digits in an integer.
 *
 * This function calculates the number of digits in the given integer `n`.
 * If the integer is negative, it also counts the negative sign.
 *
 * @param n The integer whose digits are to be counted.
 *
 * @return The number of digits in `n`,
 *	including the negative sign if applicable.
 */
static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

/**
 * @brief Converts an integer to a string representation.
 *
 * The function converts the given integer `n` into its string representation
 * and stores it in the provided buffer `str`. It fills the string from the
 * end based on the specified number of digits.
 *
 * @param str The buffer to store the string representation of the integer.
 * @param n The integer to be converted to a string.
 * @param digitcount The total number of digits in the integer, used to
 *                   determine the placement in the string.
 *
 * @return A pointer to the string representation of the integer.
 */
static char	*ft_putnbr(char *str, int n, int digitcount)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		str[digitcount - 1 - i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	return (str);
}

/**
 * @brief Converts an integer to a dynamically allocated string.
 *
 * The function converts the integer `n` into its string representation
 * (base 10) and returns a pointer to the newly allocated string. If the
 * integer is 0, it returns the string "0". If memory allocation fails,
 * it returns `NULL`.
 *
 * @param n The integer to be converted to a string.
 *
 * @return A pointer to the string representation of the integer, or `NULL`
 *         if memory allocation fails.
 *
 * @note The function handles the edge case of the minimum integer value
 *       (-2147483648) separately to avoid overflow.
 */
char	*ft_itoa(int n)
{
	int		digitcount;
	char	*str;

	digitcount = ft_count(n);
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (digitcount + 1));
	if (!str)
		return (NULL);
	str[digitcount] = '\0';
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (ft_putnbr(str, n, digitcount));
}
