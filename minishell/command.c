/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:18:25 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 21:24:33 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

COMMAND	*make_bare_simple_command(void)
{
	COMMAND		*command;
	SIMPLE_COM	*temp;

	command = (COMMAND *)xmalloc(sizeof(COMMAND));
	command->value.Simple = temp = (SIMPLE_COM *)xmalloc(sizeof(SIMPLE_COM));
	temp->flags = 0;
	temp->line = line_number;
	temp->words = (WORD_LIST *)NULL;
	temp->redirects = (REDIRECT *)NULL;
	command->type = cm_simple;
	command->redirects = (REDIRECT *)NULL;
	command->flags = 0;
	return (command);
}