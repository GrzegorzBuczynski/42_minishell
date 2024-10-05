/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_colector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:57:46 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 19:32:56 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_collector(void *content, bool do_free, int lst_nr)
{
	static t_list	*to_free;
	long			i;

	i = (long)content;
	if (do_free)
	{
		if (i > 1000)
			gc_find_and_free_node_in_lst(content, &to_free, do_free);
		else
			gc_free_level(&to_free, do_free, lst_nr);
		return (NULL);
	}
	else
		gc_calloc_internal(content, &to_free, lst_nr);
	return (content);
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
