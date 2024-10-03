/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:38:48 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies a function to each character of a string,
 *	creating a new string.
 *
 * This function takes a string `s` and a function pointer `f`, applies `f`
 * to each character of `s`, and creates a new string with the results. The
 * function `f` takes an index and a character as parameters and returns a
 * new character.
 *
 * @param s A pointer to the null-terminated string to be processed.
 * @param f A pointer to the function that will be applied to each character
 *          of `s`. It takes an unsigned integer (the index of the character)
 *          and a character, and returns a character.
 *
 * @return A pointer to the newly created string with the transformed
 * characters, or NULL if memory allocation fails or if `s` is NULL.
 *
 * @note The returned string must be freed by the caller to avoid memory leaks.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char const	*ptr;
	char		*result;
	int			i;

	ptr = s;
	i = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (result == NULL)
		return (NULL);
	while (ptr[i] != '\0')
	{
		result[i] = (*f)(i, ptr[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
