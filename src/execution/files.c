/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:18:49 by ja                #+#    #+#             */
/*   Updated: 2024/10/02 20:12:32 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
returns the status of the file
1 - a directory
2 - no execute permission
4 - no read permission
8 - no write permission
128 - file does not exist
*/
int	check_file(char *path)
{
	struct stat	info;
	int			status;

	status = 0;
	if (access(path, F_OK) != 0)
		return (128);
	if (stat(path, &info) != 0)
		return (128);
	if (S_ISDIR(info.st_mode))
		status |= 1;
	if (access(path, X_OK) != 0)
		status |= 2;
	if (access(path, R_OK) != 0)
		status |= 4;
	if (access(path, W_OK) != 0)
		status |= 8;
	return (status);
}
