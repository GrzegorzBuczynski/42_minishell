/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/07 18:37:00 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	update_or_add_env_var(t_data *minishell, char *key, char *value)
{
	t_env	*env;
	int		updated;

	env = minishell->envlist;
	updated = 0;
	while (env != NULL)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			env->value = ft_strdup(value);
			if (!env->value)
				return (0);
			updated = 1;
			return (1);
		}
		env = env->next;
	}
	if (!updated)
	{
		environment_new_node_end(&minishell->envlist, key, value);
		return (1);
	}
	return (0);
}

int	validate_key(const char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 0;
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_sign(char *argv, char sign)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == sign)
			return (1);
		i++;
	}
	return (0);
}

int	process_export_argument(char *argv, t_data *minishell)
{
	char	*key;
	char	*value;
	char	*equals_sign;

	key = argv;
	value = NULL;
	equals_sign = ft_strchr(argv, '=');
	if (equals_sign)
	{
		*equals_sign = '\0';
		value = equals_sign + 1;
	}
	if (!validate_key(key))
	{
		ft_putstr_fd("minishell: not a valid identifier\n", 2);
		minishell->exit_status = 1;
		return (0);
	}
	return (update_or_add_env_var(minishell, key, value));
}

int	ft_export(char *argv, t_data *minishell)
{
	int	result;

	if (!argv)
	{
		print_environment_sorted(minishell->envlist);
		return (1);
	}
	result = process_export_argument(argv, minishell);
	if (result == 0)
		return (0);
	return (1);
}
