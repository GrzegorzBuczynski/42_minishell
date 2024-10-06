/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/07 00:03:35 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		ft_print_error("bash error: too many arguments\n");
		gc_free_all();
		exit(1);
	}
	if (args[1])
	{
		if (!ft_is_string_numeric(args[1]))
		{
			ft_print_error("bash error: numeric argument required\n");
			gc_free_all();
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		exit_code = get_exit_code(exit_code);
	}
	ft_putstr_fd("exit\n", 2);
	gc_free_all();
	exit(exit_code);
}
