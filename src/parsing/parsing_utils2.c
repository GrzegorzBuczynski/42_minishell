/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/01 17:40:51 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*redircmd(char *file, int mode, int fd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->sub_cmd = NULL;
	cmd->file = file; /// file is the name of the file to redirect to
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd	*listcmd(t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*backcmd(t_cmd *subcmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->sub_cmd = subcmd;
	return ((t_cmd *)cmd);
}

int	read_file_access(t_data *minishell, char *file)
{
	if (access(file, F_OK | R_OK) != 0)
	{
		perror("access error");
		(void)minishell;
		return (false);
	}
	// if (access(file, F_OK | R_OK) != 0)
	// Check if file exists and is readable
	// {
	// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
	// 	ft_putstr_fd(file, STDERR_FILENO);
	// 	ft_putstr_fd(": No such file or permission denied\n", STDERR_FILENO);
	// 	minishell->exit_status = 1; // Update exit status
	// 	return (false);
	// }
	return (true);
}



t_cmd	*inputcmd(char *file, int mode, t_data *minishell, char **ps)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	if (!cmd)
		return (NULL);
	// ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->sub_cmd = NULL;
	cmd->file = file;
	cmd->fd = 0;
	cmd->mode = mode;
	if (!read_file_access(minishell, file))
	{
		*ps = NULL;
		if (cmd)
			free(cmd);
		if (file)
			free(file);
		if (minishell->exec_cmd)
			free(minishell->exec_cmd);
		if (minishell->redir_cmd)
			free(minishell->redir_cmd);
				// free the command add function to free the commands
		minishell->exec_cmd = NULL;
		minishell->redir_cmd = NULL;
		minishell->error = true;
		return (NULL);
	}
	return (cmd);
}

int	handle_output_redirection(t_data *minishell, char *file, int mode)
{
	int flags = O_WRONLY | O_CREAT | mode; // Mode can be O_TRUNC or O_APPEND
	int fd = open(file, flags, 0644);      // Open file with write permissions
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Cannot open or create file\n", STDERR_FILENO);
		minishell->exit_status = 1; // Update exit status
		return (-1);
	}
	return (fd); // Return file descriptor
}
