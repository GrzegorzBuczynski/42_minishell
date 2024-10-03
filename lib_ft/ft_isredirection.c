/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isredirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 20:17:28 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given string is a redirection operator.
 *
 * This function checks if the input string corresponds to one of the
 * standard redirection operators in shell commands:
 * - '<<' (input redirection)
 * - '>>' (output redirection, append)
 * - '>' (output redirection, overwrite)
 * - '<' (input redirection)
 *
 * The function returns a specific character indicating the type of 
 * redirection, or 0 if the string does not match any of the operators.
 *
 * @param s The string to be checked for redirection operators.
 * 
 * @return 
 * - '-' if the string is '<<' (here-document),
 * - '+' if the string is '>>' (append output),
 * - '>' if the string is '>' (overwrite output),
 * - '<' if the string is '<' (input redirection),
 * - 0 if none of the operators match.
 */
int	ft_isredirection(char *s)
{
	if (!ft_strncmp(s, "<<", 2))
		return ('-');
	else if (!ft_strncmp(s, ">>", 2))
		return ('+');
	else if (!ft_strncmp(s, ">", 1))
		return ('>');
	else if (!ft_strncmp(s, "<", 1))
		return ('<');
	return (0);
}
