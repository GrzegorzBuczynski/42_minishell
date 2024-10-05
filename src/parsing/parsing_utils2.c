/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 01:36:44 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*redircmd(char *file, int mode, int fd)
{
	t_cmd	*cmd;

	cmd = gc_calloc(sizeof(*cmd), 1);
	cmd->type = REDIR;
	cmd->sub_cmd = NULL;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd	*inputcmd(char *file)
{
	t_cmd	*cmd;

	cmd = gc_calloc(sizeof(*cmd), 2);
	if (!cmd)
		return (NULL);
	cmd->type = REDIR;
	cmd->sub_cmd = NULL;
	cmd->file = file;
	cmd->fd = 0;
	cmd->mode = O_RDONLY;
	return (cmd);
}

int	handle_output_redirection(t_data *minishell, char *file, int mode)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT | mode;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Cannot open or create file\n", STDERR_FILENO);
		minishell->exit_status = 1;
		return (-1);
	}
	return (fd);
}
