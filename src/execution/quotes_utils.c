/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:27:50 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/02 20:14:01 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotess(char **str)
{
	int	len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if ((len >= 2 && (*str)[0] == '\'' && (*str)[len - 1] == '\'') || (len >= 2
			&& (*str)[0] == '"' && (*str)[len - 1] == '"'))
	{
		ft_memmove(*str, *str + 1, len - 2);
		(*str)[len - 2] = '\0';
	}
}

char	*remove_quotes(char *s)
{
	char	*result;
	int		wait_for;
	int		i;

	result = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
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
