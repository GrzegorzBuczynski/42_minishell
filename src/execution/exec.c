/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 01:43:00 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_redirect(t_cmd *rcmd, t_data *minishell)
{
	int	fd;

	if (rcmd->mode == O_RDONLY)
		read_file_access(rcmd->file);
	close(rcmd->fd);
	fd = open(rcmd->file, rcmd->mode, 0644);
	if (fd < 0)
		ft_panic("open", 1);
	if (rcmd->sub_cmd)
		runcmd(rcmd->sub_cmd, minishell);
}

void	print_error2(char *cmd, char *message, int status)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	exit(status);
}

void	execute_binary(t_cmd *cmd, t_data *minishell)
{
	char	**envp;
	int		status;
	char	*path;

	if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
	{
		status = check_file(cmd->argv[0]);
		if (status & 128)
			print_error2(cmd->argv[0], ": No such file or directory\n", 127);
		if (status & 1)
			print_error2(cmd->argv[0], ": Is a directory\n", 126);
		else if (status & 2)
			print_error2(cmd->argv[0], ": Permission denied\n", 126);
		path = ft_strdup(cmd->argv[0]);
	}
	else
		path = find_executable_path(cmd);
	envp = environment_list_to_array(minishell->envlist);
	execve(path, cmd->argv, envp);
	// gc_free((void *)2);
	// gc_free((void *)1);
	ft_panic("execve", EXIT_FAILURE);
}

void	do_exec(t_cmd *cmd, t_data *minishell)
{
	if (cmd->argv == NULL)
		return ;
	if (cmd->argv[0] == NULL)
		return ;
	cmd->argv = remove_argv_quotes(cmd->argv);
	if (!ft_strncmp(cmd->argv[0], "./minishell", 11))
		rise_level(minishell);
	if (run_builtin_cmd(cmd->argv, minishell))
	{
		// gc_free((void *)2);
		// gc_free((void *)1);
		exit(0);
	}
	execute_binary(cmd, minishell);
	exit(1);
}
