/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:08:05 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 22:03:15 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "command.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include <sys/types.h>
# include "env.h"
# include "pipe.h"
# include <signal.h>
# include <sys/wait.h>
# include "jobs.h"
# include "trap.h"

# define NO_PIPE -1
# define EXECUTION_SUCCESS 0

int			read_command(void);
static int	line_number;

struct		fd_bitmap
{
	int		size;
	char	*bitmap;
};

/* The "simple" command.  Just a collection of words and redirects. */
typedef struct simple_com
{
	int flags;           /* See description of CMD flags. */
	int line;            /* line number the command starts on */
	WORD_LIST *words;    /* The program name, the arguments,
					variable assignments, etc. */
	REDIRECT *redirects; /* Redirections to perform. */
}			SIMPLE_COM;



#endif
