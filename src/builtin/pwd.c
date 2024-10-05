/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:14:02 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/05 21:39:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(char **argv)
{
	char	*path;

	(void)argv;
	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("CWD error\n");
		return (2);
	}
	else
		printf("%s\n", path);
	// free(path);
	return (1);
}
