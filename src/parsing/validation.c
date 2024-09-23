/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:09:14 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/22 16:07:34 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* int	prelimenary_checks(char **input, t_data *shell)
{
	shell->commands = NULL;
	if (*input == NULL)
		free_and_exit(EXIT_SUCCESS);
	if (!**input)
		return (free(*input), 0);
	if (!check_empty_pipes(*input, shell))
		return (free(*input), 0);
	*input = check_pipes(input);
	if (!*input)
		exit(EXIT_FAILURE);
	if (shell->last_cmd == NULL || ft_strcmp(shell->last_cmd,
			*input) != 0)
	{
		add_history((const char *)*input);
		update_last_command(&(shell->last_cmd), *input);
	}
	return (1);
} */

void swap_string(char **str, char *new)
{
	if (*str && new && *str != new)
		free(*str);
	*str = strdup(new);
}


// void	update_last_command(t_history *history, char *new_command)
// {
// 	if (history->last_cmd)
// 		free(history->last_cmd);
// 	history->last_cmd = ft_strdup(new_command);
// 	if (!history->last_cmd)
// 		throw_error_exit(NULL, NULL, NULL, NULL);
// }

#include <stdio.h>
int main()
{
	char **str;
	swap_string(str, "Hello");
	swap_string(str, "ello");
	printf("%s\n", *str);
}