/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/01 21:37:10 by ja               ###   ########.fr       */
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



t_cmd	*inputcmd(char *file)
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
	cmd->mode = O_RDONLY;
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
