/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:31:26 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:27:45 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of elements in a linked list.
 *
 * The function traverses the linked list pointed to by `lst` and counts
 * the number of elements it contains. If the list is empty (i.e., `lst` is
 * `NULL`), the function returns 0.
 *
 * @param lst A pointer to the first element of the linked list.
 *            This pointer must not be `NULL` unless the list is empty.
 *
 * @return The number of elements in the linked list, or 0 if the list is empty.
 *
 * @note The function does not modify the linked list;
 * it only counts its elements.
 */
int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	count = 0;
	if (!lst)
		return (0);
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
