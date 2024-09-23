/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:30:12 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/22 17:21:36 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
** The strncpy() function copies at most num characters from the string src to
** dest. If num is less than the length of src, a null character is not appended
** to dest. If num is greater than the length of src, the destination is padded
** with null characters.
 */
char	*ft_strncpy(char *dest, char *src, int num)
{
	int	i;

	i = 0;
	while (i < num && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < num)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
