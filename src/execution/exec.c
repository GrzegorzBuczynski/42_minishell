/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 20:42:32 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_redirect(t_cmd *rcmd, t_data *minishell)
{
	int	fd;

	close(rcmd->fd);
	fd = open(rcmd->file, rcmd->mode, 0644);
	if (fd < 0)
		panic("open");
	runcmd(rcmd->sub_cmd, minishell);
	exit(0);
}

void	run_in_background_or_list(t_cmd *cmd, t_data *minishell)
{
	pid_t	pid_l;

	if (cmd->type == LIST)
	{
		pid_l = fork1();
		if (pid_l == 0)
			runcmd(cmd->left, minishell);
		waitpid(pid_l, NULL, 0);
		runcmd(cmd->right, minishell);
	}
	else if (cmd->type == BACK)
	{
		if (fork1() == 0)
			runcmd(cmd->sub_cmd, minishell);
	}
}

void	execute_process(char *binary_path, t_cmd *cmd, t_data *minishell)
{
	char	**envp;

	envp = environment_list_to_array(minishell->envlist);
	execve(binary_path, cmd->argv, envp);
	handle_exec_error("execve failed for: ", binary_path);
	free(envp);
	exit(EXIT_FAILURE);
}

void	do_exec(t_cmd *cmd, t_data *minishell)
{
	char	**paths;
	char	*binary_path;

	if (cmd->argv == NULL)
		return ;
	if (cmd->argv[0] == NULL)
		return ;
	if (run_builtin_cmd(cmd->argv, minishell))
		exit(0);
	paths = retrieve_paths();
	binary_path = find_executable_path(cmd, paths);
	execute_process(binary_path, cmd, minishell);
	clean_up(binary_path, paths);
	exit(1);
}

void	do_pipe(t_cmd *cmd, t_data *minishell)
{
	create_pipes(cmd, minishell);
	make_forks(cmd, minishell);
}

void	runcmd(t_cmd *cmd, t_data *minishell)
{
	if (cmd == 0)
		exit(1);
	if (cmd->type == 0)
		exit(1);
	if (cmd->type == EXEC)
		do_exec(cmd, minishell);
	else if (cmd->type == PIPE)
		do_pipe(cmd, minishell);
	else if (cmd->type == REDIR)
		do_redirect(cmd, minishell);
	else if (cmd->type == LIST || cmd->type == BACK)
		run_in_background_or_list(cmd, minishell);
	else if (cmd->type == HERE_DOC)
		do_here_doc(cmd, minishell);
	else
		exit(1);
	return ;
}
