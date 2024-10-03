/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_panic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:06:21 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 19:30:58 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs an error message and terminates the program.
 *
 * The function prints an error message to the standard error output using 
 * the `perror` function, based on the provided string `s`. It then 
 * terminates the program with the given exit status.
 *
 * @param s A string that describes the error, which is printed 
 *          alongside the system error message.
 * @param status An integer representing the exit status code for 
 *               the program termination. Typically, a non-zero value 
 *               indicates an error.
 * 
 * @note This function is used for error handling and should be called 
 *       when a critical error occurs that necessitates immediate 
 *       program termination.
 */
void	ft_panic(char *s, int status)
{
	perror(s);
	exit(status);
}
