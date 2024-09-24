/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:52:49 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/24 21:28:25 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
** The ft_strndup() function allocates sufficient memory for a copy of the string s,
** does the copy, and returns a pointer to it. The pointer may subsequently be used
** as an argument to the function free(3). If insufficient memory is available, NULL
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*newstr;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
