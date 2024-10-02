/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_colector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:57:46 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/02 19:21:31 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del(void *to_free)
{
	free(to_free);
}

void	*gc_collector(void *content, bool free)
{
	static t_list	*to_free;

	if (free)
	{
		ft_lstclear(&to_free, del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&to_free, ft_lstnew(content));
		return (content);
	}
}

void	ft_clear_envlist(t_data *minishell)
{
	t_env	*envlist;
	t_env	*envlist_free;

	envlist = minishell->envlist;
	while (envlist)
	{
		envlist_free = envlist;
		envlist = envlist->next;
		free(envlist_free);
	}
	minishell->envlist = NULL;
}
