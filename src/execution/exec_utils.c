/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:10:48 by ja                #+#    #+#             */
/*   Updated: 2024/10/02 19:55:54 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	read_file_access(char *file)
{
	if (access(file, F_OK | R_OK) != 0)
	{
		perror("access error");
		exit(1);
	}
}
