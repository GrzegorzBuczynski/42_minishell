/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:04:01 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 18:10:31 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_builtin_cmd(char **argv, t_data *minishell)
{
	int	ret;

	(void)minishell;
	ret = 0;
	if (ft_strcmp(argv[0], "cd") == 0)
		ret = ft_cd(argv, minishell);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ret = ft_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
	{
		if (!minishell->envlist)
			return (0);
		print_environment(minishell->envlist);
		return (1);
	}
	else if (ft_strcmp(argv[0], "export") == 0)
		ret = ft_export(argv[1], minishell);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ret = ft_pwd(argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ret = ft_unset(argv, minishell);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ret = ft_exit(argv);
	return (ret);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->argv)
		return (0);
	if (ft_strcmp(cmd->argv[0], "cd") == 0 || ft_strcmp(cmd->argv[0],
			"echo") == 0 || ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0 || ft_strcmp(cmd->argv[0],
			"pwd") == 0 || ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}
