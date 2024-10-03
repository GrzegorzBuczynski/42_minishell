/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:26:25 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Helper function to create a new linked list by applying
 * a function to each element.
 *
 * The function traverses the linked list pointed to by `lst`, applies the
 * function pointed to by `f` to the content of each element, and constructs
 * a new linked list with the results. If any application of `f` returns `NULL`,
 * the function clears the new list and returns `NULL`.
 *
 * @param lst A pointer to the first element of the original linked list.
 * @param f A pointer to a function that takes a `void*` as an argument and
 *          returns a new content for the element.
 * @param del A pointer to a function that takes a `void*` as an argument and
 *            is used to free the content of the elements in case of failure.
 *
 * @return A pointer to the new linked list,
	or `NULL` if memory allocation fails
 *         or if `f` returns `NULL` for any element.
 */
static t_list	*ft_help(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*node;
	void	*inside;

	newlist = NULL;
	while (lst != NULL)
	{
		inside = f(lst->content);
		if (!inside)
		{
			ft_lstclear(&newlist, del);
			free(newlist);
			return (NULL);
		}
		node = ft_lstnew(inside);
		if (!node)
		{
			ft_lstclear(&newlist, del);
			free(newlist);
			return (NULL);
		}
		ft_lstadd_back(&newlist, node);
		lst = lst->next;
	}
	return (newlist);
}

/**
 * @brief Creates a new linked list by applying a function to each element
 * of an existing list.
 *
 * The function traverses the linked list pointed to by `lst`, applies the
 * function pointed to by `f` to the content of each element, and returns a
 * new linked list with the results. If `lst`, `f`, or `del` is `NULL`,
 * the function returns `NULL`.
 *
 * @param lst A pointer to the first element of the original linked list.
 * @param f A pointer to a function that takes a `void*` as an argument and
 *          returns the new content for the element.
 * @param del A pointer to a function that takes a `void*` as an argument and
 *            is used to free the content of the elements in case of failure.
 *
 * @return A pointer to the new linked list, or `NULL` if any of the input
 *         parameters are `NULL` or if memory allocation fails.
 *
 * @note The function will clear the newly created list if any application
 *       of `f` returns `NULL`.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	newlist = ft_help(lst, f, del);
	return (newlist);
}
