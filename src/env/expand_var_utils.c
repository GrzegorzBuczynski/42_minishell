/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:41:35 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/06 15:53:10 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_another_space(int i, int quotes, char *input)
{
	if (input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0'
		&& quotes == NOT_SET)
		return (1);
	else if (((input[i] == '<' && input[i + 1] != '<') || (input[i] == '>'
				&& input[i + 1] != '>')) && input[i + 1] != ' ' && input[i
			+ 1] != '\0' && quotes == NOT_SET)
		return (1);
	return (0);
}

int	add_space(int i, int quotes, char *input)
{
	if (i > 0 && input[i] == '|' && input[i - 1] != ' ' && quotes == NOT_SET)
		return (1);
	else if (i > 0 && ((input[i] == '>' && input[i - 1] != '>')
			|| (input[i] == '<' && input[i - 1] != '<')) && input[i - 1] != ' '
		&& quotes == NOT_SET)
		return (1);
	return (0);
}

bool	do_copy_var(int quotes, char *input, int i)
{
	return ((input[i] == '$' && quotes != '\'' && input[i + 1] != ' ' && input[i
				+ 1] != '\"' && input[i + 1] != '+' && input[i + 1] != ':'
			&& input[i + 1] != '/' && input[i + 1] != '=' && input[i + 1] != '.'
			&& input[i + 1] != ',' && input[i + 1] != '\0'));
}

void	set_quotes(char *quotes, char word)
{
	if (*quotes == NOT_SET && (word == '\'' || word == '\"'))
		*quotes = word;
	else if (*quotes != NOT_SET && word == *quotes)
		*quotes = NOT_SET;
}

int	copy_variable(char *name, t_data *minishell, int *j, char *result)
{
	if (!name)
		return (0);
	ft_strlcpy(result + *j, ft_get_var_value(name, minishell),
		ft_strlen(ft_get_var_value(name, minishell)) + 1);
	*j += ft_strlen(ft_get_var_value(name, minishell));
	return (1);
}
