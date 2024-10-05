/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/05 21:39:35 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	find_and_remove_env(t_env **env_list, const char *key)
{
	t_env	*env;
	t_env	*prev;

	env = *env_list;
	prev = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				*env_list = env->next;
			// free(env->key);
			// free(env->value);
			// free(env);
		}
		prev = env;
		env = env->next;
	}
}

// There isn't input validation for incorrect syntax
int	ft_unset(char **argv, t_data *minishell)
{
	char	*key;

	if (!argv || !argv[0])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	key = argv[1];
	if (!key)
		return (0);
	find_and_remove_env(&minishell->envlist, key);
	return (1);
}
