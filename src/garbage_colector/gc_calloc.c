/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:49:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 01:37:27 by ja               ###   ########.fr       */
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
	t_list	**debag;
	t_list	*debag2;
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
			// if (!tmp)
			// 	tmp = new_node;
			ft_lstadd_back((t_list **)&(tmp->content), ft_lstnew(content));
			debag = (t_list **)&(tmp->content);
			debag2 = *debag;
			(void)debag;
			(void)debag2;
			return (TRUE);
		}
		i++;
		tmp = tmp->next;
	}
	return (FALSE);
}
