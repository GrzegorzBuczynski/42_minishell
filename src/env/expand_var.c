/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:37:33 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/02 19:42:16 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	replace_var_loop(char *input, t_data *minishell, char *result, int i)
{
	int		j;
	char	quotes;

	j = 0;
	quotes = NOT_SET;
	while (input[i])
	{
		set_quotes(&quotes, input[i]);
		if (!do_copy_var(quotes, input, i))
		{
			if (add_space(i, quotes, input))
				result[j++] = ' ';
			result[j] = input[i];
			if (add_another_space(i, quotes, input))
				result[++j] = ' ';
			i++;
			j++;
		}
		else
		{
			i++;
			copy_variable(get_var_name(input, &i), minishell, &j, result);
		}
	}
	return (1);
}

int	count_length(char *input, t_data *minishell, int *length)
{
	bool	is_in_quotes;
	char	*name;
	int		i;

	i = 0;
	is_in_quotes = false;
	while (input[i])
	{
		if (input[i] == '\'')
			is_in_quotes = !is_in_quotes;
		if (input[i] == '$' && !is_in_quotes && input[i + 1] != ' ' && input[i
				+ 1] != '\"' && input[i + 1] != '\0')
		{
			i++;
			name = get_var_name(input, &i);
			if (!name)
				return (ERROR);
			if (*name == '?')
				*length += ft_strlen(ft_itoa(minishell->exit_status));
			else
				*length += ft_strlen(ft_get_var_value(name, minishell)) + 1;
			free(name);
		}
		else
			check_for_spaces(input, length, &i, is_in_quotes);
	}
	return (*length);
}

char	*replace_var(char *input, t_data *minishell)
{
	int		length;
	char	*result;

	length = 0;
	count_length(input, minishell, &length);
	if (length <= 0)
		return (NULL);
	result = (char *)ft_calloc(length + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (!replace_var_loop(input, minishell, result, 0) || !result)
		return (free(result), NULL);
	return (result);
}

void	set_last_exit_code(t_data *minishell)
{
	t_env	*envlst;
	char	*value;

	envlst = minishell->envlist;
	while (envlst)
	{
		if (!ft_strcmp("?", envlst->key))
		{
			value = ft_itoa(minishell->exit_status);
			if (value)
			{
				free(envlst->value);
				envlst->value = value;
			}
			return ;
		}
		envlst = envlst->next;
	}
}
