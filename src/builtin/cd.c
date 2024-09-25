/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:15:20 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/25 19:27:35 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_change_pwd(t_data *minishell)
{
	char	*cwd;

	cwd = gc_collector(getcwd(NULL, 0), false);
	if (!cwd)
		return (0);
	return (ft_update_env_list("PWD", cwd, false, minishell), 0);
}

static int	ft_cd_home(t_data *minishell)
{
	char	*home;

	ft_update_env_list("OLDPWD", ft_get_var_value("PWD", minishell), false,
		minishell);
	home = ft_get_var_value("HOME", minishell);
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == true)
		return (ft_update_env_list("PWD", home, false, minishell), 0);
	return (0);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	md_cd(char **argv, t_data *minishell)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		minishell->exit_status = 1;
		return (1);
	}
	if (!argv[1])
		return (ft_cd_home(minishell));
	if (chdir(argv[1]) == error)
	{
		minishell->exit_status = 1;
		return (ft_cd_err_msg(argv[1]));
	}
	ft_update_env_list("OLDPWD", ft_get_var_value("PWD", minishell), false,
		minishell);
	return (ft_change_pwd(minishell));
}
