/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:41:01 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/03 20:14:51 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given string is a pipe character.
 *
 * This function takes a string as input and checks whether it starts with
 * the pipe character ('|'). If it does, the function returns the ASCII value
 * of the pipe character; otherwise, it returns 0.
 *
 * @param s The string to be checked.
 * 
 * @return The ASCII value of the pipe character if the string matches; 
 *         otherwise, returns 0.
 *
 * @note The function only checks the first character of the string.
 */
int	ft_ispipe(char *s)
{
	if (s && !ft_strncmp(s, "|", 1))
		return ('|');
	return (0);
}
