/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:14:02 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/06 16:06:16 by gbuczyns         ###   ########.fr       */
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
	return (1);
}
