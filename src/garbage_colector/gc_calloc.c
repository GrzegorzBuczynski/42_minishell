/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:49:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 19:27:11 by gbuczyns         ###   ########.fr       */
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

	i = 0;
	if (!head)
		return (FALSE);
	tmp = *head;
	if (!tmp)
	{
		ft_lstadd_back(head, ft_lstnew(NULL));
		tmp = *head;
	}
	while (i <= lst_nr)
	{
		if (!tmp->next)
		{
			ft_lstadd_back(head, ft_lstnew(NULL));
		}
		if (i == lst_nr)
		{
			ft_lstadd_back((t_list **)&(tmp->content), ft_lstnew(content));
			debag = (t_list **)&(tmp->content),
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
