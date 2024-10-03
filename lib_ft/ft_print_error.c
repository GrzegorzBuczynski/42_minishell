/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 20:05:26 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints an error message to the standard error output.
 *
 * This function takes a string message as input and writes it to the standard 
 * error output (file descriptor 2). It uses the `ft_strlen` function to
 * determine the length of the message to ensure that the entire message is
 * printed.
 *
 * @param message A pointer to the string message to be printed. 
 *
 * @note This function does not append a newline character to the message. It 
 *       assumes that the provided message is null-terminated.
 */
void	ft_print_error(char *message)
{
	write(2, message, ft_strlen(message));
}
