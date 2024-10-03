/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:12:00 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates over a linked list and applies a function to each element.
 *
 * The function traverses the linked list pointed to by `lst` and applies 
 * the function pointed to by `f` to the content of each element. 
 * If `f` is `NULL`, no operation is performed.
 *
 * @param lst A pointer to the first element of the linked list. 
 *            The traversal stops when this pointer becomes `NULL`.
 * @param f A pointer to a function that takes a `void*` as an argument 
 *          and is applied to the content of each element in the list. 
 *          If `f` is `NULL`, the function does nothing.
 * 
 * @return None.
 * 
 * @note The function does not modify the linked list itself; it only 
 *       applies the function to the content of its elements.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL && f)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
