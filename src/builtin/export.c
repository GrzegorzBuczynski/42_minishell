/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/22 17:51:58 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_key_and_value(char *argument)
{
	char	*delimiter_pos;
	char	**key_value;

	delimiter_pos = ft_strchr(argument, '=');
	if (!delimiter_pos)
		return (NULL);
	key_value = (char **)malloc(sizeof(char *) * 2);
	if (!key_value)
		return (NULL);
	key_value[0] = ft_strndup(argument, delimiter_pos - argument);
	if (!key_value[0])
	{
		free(key_value);
		return (NULL);
	}
	key_value[1] = ft_strdup(delimiter_pos + 1);
	if (!key_value[1])
		free (key_value[1]);
	return (key_value);
}

void	free_key_value(char **key_value)
{
	if (key_value)
	{
		free(key_value[0]);
		free(key_value[1]);
		free(key_value);
	}
}

int	update_or_add_env_var(t_data *minishell, char **key_value)
{
	t_env	*env;
	int		updated;

	env = minishell->envlist;
	updated = 0;
	while (env != NULL)
	{
		if (ft_strcmp(key_value[0], env->key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(key_value[1]);
			if (!env->value)
				return (0);
			updated = 1;
			return (1);
		}
		env = env->next;
	}
	if (!updated)
	{
		environment_new_node_end(&minishell->envlist, key_value[0],
			key_value[1]);
		return (1);
	}
	return (0);
}

int is_valid_key(const char *key) {
    if (!key || (!isalpha(key[0]) && key[0] != '_')) {
        return 0; // Key must start with an alphabetic character or '_'
    }
    for (int i = 1; key[i] != '\0'; i++) {
        if (!isalnum(key[i]) && key[i] != '_') {
            return 0; // Key can only contain alphanumeric characters and '_'
        }
    }
    return 1;
}

char *extract_value(const char *input) {
    char *value = NULL;
    if (input == NULL) return NULL;

    // Check if the value is enclosed in quotes
    if (input[0] == '"' || input[0] == '\'') {
        char quote = input[0];
        const char *end = strchr(input + 1, quote);
        if (end) {
            size_t length = end - input - 1;
            value = malloc(length + 1);
            strncpy(value, input + 1, length);
            value[length] = '\0';
        }
    } else {
        // No quotes, just return the input as is (no whitespace allowed)
        if (strchr(input, ' ') == NULL) {
            value = strdup(input);
        }
    }
    return value;
}

int ft_export(char **argv, t_data *minishell) {
    int i;

    if (argv[1] == NULL) {
        print_environment_sorted(minishell->envlist);
        return 1;
    }

    i = 1;
    while (argv[i] != NULL) {
        char *key = NULL;
        char *value = NULL;

        // Split key and value
        char *equals_sign = strchr(argv[i], '=');
        if (equals_sign) {
            size_t key_length = equals_sign - argv[i];
            key = strndup(argv[i], key_length);
            value = extract_value(equals_sign + 1);
        } else {
            key = strdup(argv[i]);
        }

        // Validate and store the key and value
        if (is_valid_key(key)) {
            // Store key and value in the environment (you need to implement this)
            if (value) {
                // Store key and value in the environment
            } else {
                // Handle the case where the value is NULL (or empty)
            }
        } else {
            fprintf(stderr, "export: `%s': not a valid identifier\n", argv[i]);
        }

        free(key);
        free(value);
        i++;
    }
    return 0;
}
