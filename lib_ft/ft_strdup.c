/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:36:26 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates a string by allocating memory for a new copy.
 *
 * The function allocates sufficient memory to hold a copy of the 
 * string pointed to by `s`, and then copies the content of `s` 
 * into the newly allocated memory, including the null terminator. 
 * If memory allocation fails, the function returns NULL.
 *
 * @param s A pointer to the null-terminated string to be duplicated. 
 *          This string must not be NULL.
 * 
 * @return A pointer to the newly allocated string that is a duplicate 
 *         of `s`, or NULL if memory allocation fails.
 *
 * @note The caller is responsible for freeing the memory allocated 
 *       for the duplicated string to avoid memory leaks.
 */
char	*ft_strdup(const char *s)
{
	char			*ptr;
	unsigned int	i;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
