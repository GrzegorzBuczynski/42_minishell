/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:33:00 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes an integer to the specified file descriptor as a string.
 *
 * The function converts the integer `n` to its string representation 
 * and writes it to the file descriptor `fd`. It handles special cases 
 * for zero, negative numbers, and the minimum integer value.
 *
 * @param n The integer to be written.
 * @param fd The file descriptor to which the integer will be written. 
 *           Common values include 1 for standard output and 2 for 
 *           standard error.
 * 
 * @note The function does not perform error checking on the write operations. 
 *       If the write fails, the behavior is not defined. The function also 
 *       correctly handles the edge case of `-2147483648`, which cannot 
 *       be represented as a positive number due to integer overflow.
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n / 10 != 0)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
	else
		ft_putchar_fd('0' + n, fd);
}
