/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 20:01:59 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *message)
{
	write(2, message, ft_strlen(message));
}

int	get_exit_code(int code)
{
	if (code < 0)
		return (256 + (code % 256));
	return (code % 256);
}

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1] && args[2])
	{
		print_error("bash error: too many arguments\n");
		exit(1);
	}
	if (args[1])
	{
		if (!ft_is_string_numeric(args[1]))
		{
			print_error("bash error: numeric argument required\n");
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		exit_code = get_exit_code(exit_code);
	}
	exit(exit_code);
}
