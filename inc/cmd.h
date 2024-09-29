/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:08:04 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 19:10:23 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# define MAXARGS 100

# define EXEC 1
# define BUILTIN 2
# define HERE_DOC 3
# define INREDIR 4
# define REDIR 5
# define PIPE 6
# define LIST 7
# define BACK 8

# define ECHO 31
# define CD 32

typedef struct s_cmd
{
	int				type;
	char			**argv;
	char			*paths;
	char			*flag;
	char			*file;
	int				mode;
	int				fd;
	struct s_cmd	*sub_cmd;
	struct s_cmd	*redir_cmd;
	struct s_cmd	*exec_cmd;
	struct s_cmd	*left;
	struct s_cmd	*right;

}					t_cmd;

#endif