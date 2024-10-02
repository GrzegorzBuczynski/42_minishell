/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:13:40 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/02 19:54:13 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*environment_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	environment_new_node_end(t_env **head, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = environment_new_node(key, value);
	if (!new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	init_environment(t_env **environment, char **env)
{
	char	*key;
	char	*value;
	char	*delimiter_pos;
	int		i;

	*environment = NULL;
	i = 0;
	while (env[i])
	{
		delimiter_pos = ft_strchr(env[i], '=');
		if (delimiter_pos != NULL)
		{
			key = ft_strndup(env[i], delimiter_pos - env[i]);
			value = ft_strdup(delimiter_pos + 1);
			environment_new_node_end(environment, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	key = ft_strndup("?", 1);
	value = ft_strdup("0");
	environment_new_node_end(environment, key, value);
	free(key);
	free(value);
}

void	environment_free_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	print_environment(t_env *node)
{
	t_env	*current;

	current = node;
	while (current != NULL)
	{
		if (!(*(current->key) == '?'))
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
