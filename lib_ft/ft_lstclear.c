/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:10:59 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Clears and frees a linked list.
 *
 * The function iterates through the linked list pointed to by `lst`, 
 * calling the function pointed to by `del` on the content of each 
 * element and then freeing each element from memory. After clearing 
 * the list, it sets the pointer to the head of the list to `NULL`.
 *
 * @param lst A pointer to a pointer to the first element of the list. 
 *            This allows modification of the head of the list.
 * @param del A pointer to a function that takes a `void*` as an 
 *            argument and is used to free the content of each element. 
 *            This function must not be `NULL`.
 * 
 * @return None.
 * 
 * @note The function does not free the list itself; it only frees 
 *       the individual elements and their contents.
 * 
 * @warning If either `lst` or `del` is `NULL`, the function does nothing 
 *          and returns immediately.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free (current);
		current = next;
	}
	*lst = NULL;
}
