/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:49:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 18:05:37 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*gc_calloc(size_t size, int lst_nr)
{
	void	*ptr;

	ptr = ft_calloc(size, 1);
	gc_collector(ptr, false, lst_nr);
	return (ptr);
}

int	gc_calloc_internal(void *content, t_list **head, int lst_nr)
{
	t_list	*tmp;
	int		i;

	i = 0;
	if (!head || !*head)
		return (FALSE);
	tmp = *head;
	while (tmp)
	{
		if (i == lst_nr)
		{
			ft_lstadd_back(&tmp->content, ft_lstnew(content));
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}
