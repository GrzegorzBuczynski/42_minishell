/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/02 12:45:21 by ja               ###   ########.fr       */
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
		panic("open", 1);
	if (rcmd->sub_cmd)
		runcmd(rcmd->sub_cmd, minishell);
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

void	execute_binary(char *binary_path, t_cmd *cmd, t_data *minishell)
{
	char	**envp;
	int		status;

	if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
	{
		status = check_file(cmd->argv[0]);
		if (status & 128)
			print_error(cmd->argv[0], ": No such file or directory\n", 127);
		if (status & 1)
			print_error(cmd->argv[0], ": Is a directory\n", 126);
		else if (status & 2)
			print_error(cmd->argv[0], ": Permission denied\n", 126);
		path = ft_strdup(cmd->argv[0]);
	}
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
	cmd->argv = remove_argv_quotes(cmd->argv);
	if (run_builtin_cmd(cmd->argv, minishell))
		exit(0);
	// if(minishell->redir_cmd || minishell->pipe_cmd)
	paths = retrieve_paths();
	binary_path = find_executable_path(cmd, paths);
	execute_binary(binary_path, cmd, minishell);
	clean_up(binary_path, paths);
	exit(1);
}

int	exec_with_pipes(t_data *minishell)
{
	if (minishell->fork_cmd)
	{
		create_pipes(minishell->fork_cmd, minishell);
		make_forks(minishell->fork_cmd, minishell);
		return (1);
	}
	return (0);
}

void	runcmd(t_cmd *cmd, t_data *minishell)
{
	if (cmd == 0)
		exit(1);
	if (cmd->type == 0)
		exit(1);
	if (cmd->type == EXEC)
		do_exec(cmd, minishell);
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

int	exec_with_redirects(t_data *minishell)
{
	pid_t	last_pid;

	if (minishell->redir_cmd)
	{
		last_pid = fork1();
		if (last_pid == 0)
		{
			runcmd(minishell->redir_cmd, minishell);
			runcmd(minishell->exec_cmd, minishell);
		}
		wait_for_processes(minishell, last_pid);
		return (1);
	}
	return (0);
}

int	exec_exec_cmd(t_data *minishell)
{
	pid_t	last_pid;
	t_cmd	*cmd;

	if (minishell->exec_cmd)
	{
		cmd = minishell->exec_cmd;
		if (is_builtin(cmd))
		{
			run_builtin_cmd(cmd->argv, minishell);
			return (1);
		}
		else
		{
			last_pid = fork1();
			if (last_pid == 0)
				runcmd(minishell->commands[0], minishell);
		}
		wait_for_processes(minishell, last_pid);
	}
	return (0);
}

int	execute(t_data *minishell)
{
	if (exec_with_pipes(minishell))
		return (0);
	else if (exec_with_redirects(minishell))
		return (0);
	else if (exec_exec_cmd(minishell))
		return (0);
	return (0);
}
