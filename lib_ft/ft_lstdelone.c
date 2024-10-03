/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:11:39 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes a single element from a linked list.
 *
 * The function takes a pointer to a linked list element `lst` and 
 * frees the memory allocated for its content by calling the function 
 * pointed to by `del`. After freeing the content, it frees the memory 
 * allocated for the element itself.
 *
 * @param lst A pointer to the element to be deleted from the list. 
 *            This must not be `NULL`.
 * @param del A pointer to a function that takes a `void*` as an 
 *            argument and is used to free the content of the element. 
 *            This must not be `NULL`.
 * 
 * @return None.
 * 
 * @warning If either `lst` or `del` is `NULL`, the function does nothing 
 *          and returns immediately.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
