/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:18:13 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 18:55:39 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*ft_envlist_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_update_env_list(char *key, char *value, bool yes,
		t_data *minishell)
{
	t_env	*envlist;

	envlist = minishell->envlist;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
		{
			if (value)
				envlist->value = ft_strdup(value);
			return ;
		}
		envlist = envlist->next;
	}
	if (yes)
		ft_envlstadd_back(ft_envlist_new(key, value), minishell);
}

bool	ft_env_entry_exists(char *key, t_data *minishell)
{
	t_env	*envlst;

	envlst = minishell->envlist;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

char	*ft_get_var_value(char *key, t_data *minishell)
{
	t_env	*envlst;

	envlst = minishell->envlist;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	ft_envlstadd_back(t_env *new, t_data *minishell)
{
	t_env	*curr;

	if (!minishell->envlist)
	{
		minishell->envlist = new;
		return ;
	}
	curr = minishell->envlist;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}
