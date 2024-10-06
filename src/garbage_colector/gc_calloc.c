/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:49:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 16:05:33 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*gc_calloc(size_t size, int lst_nr)
{
	void	*ptr;

	ptr = ft_calloc(size, 1);
	if (!ptr)
		return (NULL);
	gc_collector(ptr, false, lst_nr);
	return (ptr);
}

int	gc_calloc_internal(void *content, t_list **head, int lst_nr)
{
	t_list	*tmp;
	int		i;
	t_list	*new_node;

	i = 1;
	if (!head)
		return (FALSE);
	tmp = *head;
	while (i <= lst_nr)
	{
		if (!tmp)
		{
			new_node = ft_lstnew(NULL);
			ft_lstadd_back(head, new_node);
			tmp = *head;
		}
		if (i == lst_nr)
		{
			ft_lstadd_back((t_list **)&(tmp->content), ft_lstnew(content));
			return (TRUE);
		}
		i++;
		tmp = tmp->next;
	}
	return (FALSE);
}

void	remove_node(t_list **to_free, t_list *previous, t_list *current)
{
	if (previous)
	{
		previous->next = current->next;
		current->next = NULL;
	}
	else
	{
		*to_free = current->next;
	}
	ft_free_lst_and_content(current);
}

int	gc_free_level(t_list **to_free, bool do_free, int lst_nr)
{
	t_list	*tmp;
	t_list	*previous;
	int		i;

	if (!to_free || !do_free)
		return (FALSE);
	tmp = *to_free;
	previous = NULL;
	i = 1;
	while (tmp)
	{
		if (i == lst_nr)
		{
			remove_node(to_free, previous, tmp);
			return (TRUE);
		}
		previous = tmp;
		tmp = tmp->next;
		i++;
	}
	return (FALSE);
}
