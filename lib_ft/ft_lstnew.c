/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:27:10 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a new linked list element.
 *
 * The function allocates memory for a new linked list element, initializes 
 * its content with the provided `content`, and sets its `next` pointer to 
 * `NULL`. If memory allocation fails, it returns `NULL`.
 *
 * @param content A pointer to the content to be assigned to the new element.
 * 
 * @return A pointer to the newly created linked list element, or `NULL` 
 *         if memory allocation fails.
 * 
 * @note The caller is responsible for managing the memory of the `content` 
 *       provided. The function does not make a copy of the content.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
