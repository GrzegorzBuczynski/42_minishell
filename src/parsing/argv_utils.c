/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:31:05 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/05 21:35:21 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_cmd_argv(t_cmd *cmd)
{
	if (cmd->argv == NULL)
	{
		cmd->argv = gc_calloc(sizeof(char *), 1);
		cmd->argv[0] = ft_strdup("");
	}
}

/*
** Append a line to the argv array
*/
char	**ft_append_argv(char **argv, char *line)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (argv && argv[i])
		i++;
	new_argv = ft_calloc(sizeof(char *) * (i + 2), 1);
	if (new_argv == NULL)
		ft_panic("malloc", 1);
	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i] = gc_collector(ft_strdup(line), false, 0);
	new_argv[i + 1] = NULL;
	return (new_argv);
}
