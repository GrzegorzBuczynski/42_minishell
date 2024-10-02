/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/02 20:09:43 by ssuchane         ###   ########.fr       */
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
	cmd->file = file;
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
