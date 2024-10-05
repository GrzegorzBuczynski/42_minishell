/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:27:50 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 21:36:33 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_quotes(char *s)
{
	char	*result;
	int		wait_for;
	int		i;

	result = (char *)gc_calloc((ft_strlen(s) + 1)*sizeof(char), 1);
	if (!result)
		return (NULL);
	wait_for = NOT_SET;
	i = 0;
	while (*s)
	{
		if (*s == '\'' && wait_for == NOT_SET)
			wait_for = '\'';
		else if (*s == '\"' && wait_for == NOT_SET)
			wait_for = '\"';
		else if (*s == wait_for)
			wait_for = NOT_SET;
		else
		{
			result[i] = *s;
			i++;
		}
		s++;
	}
	return (result);
}

char	**remove_argv_quotes(char **argv)
{
	int	i;

	if (!argv)
		return (NULL);
	i = 1;
	while (argv[i])
	{
		argv[i] = remove_quotes(argv[i]);
		i++;
	}
	return (argv);
}

void	rise_level(t_data *minishell)
{
	char	*level;
	char	*new_level;

	level = ft_get_var_value("SHLVL", minishell);
	if (level == NULL)
		return ;
	new_level = ft_itoa(ft_atoi(level) + 1);
	if (new_level == NULL)
		return ;
	ft_update_env_list("SHLVL", new_level, YES, minishell);
	free(new_level);
}
