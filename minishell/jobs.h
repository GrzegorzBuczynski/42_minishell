/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:00:37 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 22:00:49 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

/* flags for make_child () */
#define FORK_SYNC	0		/* normal synchronous process */
#define FORK_ASYNC	1		/* background process */
#define FORK_NOJOB	2		/* don't put process in separate pgrp */
#define FORK_NOTERM	4		/* don't give terminal to any pgrp */

#endif