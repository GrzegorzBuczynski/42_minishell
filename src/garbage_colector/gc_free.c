/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:28:14 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 18:04:22 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** gc_free is a function that frees the pointer passed as an argument. If the
** pointer is a pointer to a list, it will free the list and its content.
** If the pointer is a pointer to a pointer, it will free the pointer.
** If the pointer is a pointer to a pointer to a pointer, it will free the
** pointer to the pointer.
*/
void	*gc_free(void *ptr)
{
	if (ptr > 1000)
		gc_collector(ptr, true, 0);
	else if (ptr == 0)
		gc_collector(NULL, true, 0);
	else if (ptr <= 1000)
		gc_collector(ptr, true, (int)ptr);
	return (NULL);
}

static int	free_if_head(void *ptr, t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	if (tmp->content == ptr)
	{
		free(tmp->content);
		*head = tmp->next;
		free(tmp);
		return (TRUE);
	}
	return (FALSE);
}

static int	free_if_not_head(void *ptr, t_list **head)
{
	t_list	*tmp;
	t_list	*previous;

	previous = *head;
	tmp = (*head)->next;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			free(tmp->content);
			previous->next = tmp->next;
			free(tmp);
			return (TRUE);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (FALSE);
}

int	gc_find_and_free_node_in_lst(void *ptr, t_list **head, bool free)
{
	t_list	*list;
	t_list	*sublist;

	sublist = NULL;
	if (!ptr || !head || !free)
		return (FALSE);
	list = *head;
	while (list)
	{
		sublist = list->content;
		if (free_if_head(ptr, &sublist))
			return (TRUE);
		if (free_if_not_head(ptr, &sublist))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}

int	ft_free_lst_and_content(t_list **head)
{
	if (!head || !*head)
		return (FALSE);
	while (*head)
		gc_find_and_free_node_in_lst((*head)->content, head, TRUE);
	return (TRUE);
}

int	gc_free_level(t_list **to_free, bool do_free, int lst_nr)
{
	t_list	*tmp;
	t_list	*previous;
	int		i;

	i = 0;
	previous = NULL;
	if (!to_free || !do_free)
		return (FALSE);
	tmp = *to_free;
	while (tmp)
	{
		if (i == lst_nr)
		{
			if (previous)
				previous->next = tmp->next;
			else
				*to_free = tmp->next;
			ft_free_lst_and_content(&tmp);
			return (TRUE);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (FALSE);
}

