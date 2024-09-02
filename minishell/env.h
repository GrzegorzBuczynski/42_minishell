/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:08:06 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 20:10:13 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H


typedef struct variable {
  char *name;			/* Symbol that the user types. */
  char *value;			/* Value that is returned. */
  char *exportstr;		/* String for the environment. */
//   sh_var_value_func_t *dynamic_value;	/* Function called to return a `dynamic'
// 				   value for a variable, like $SECONDS
// 				   or $RANDOM. */
//   sh_var_assign_func_t *assign_func; /* Function called when this `special
// 				   variable' is assigned a value in
// 				   bind_variable. */
  int attributes;		/* export, readonly, array, invisible... */
  int context;			/* Which context this variable belongs to. */
} SHELL_VAR;


typedef struct _vlist {
  SHELL_VAR **list;
  int list_size;	/* allocated size */
  int list_len;		/* current number of entries */
} VARLIST;

#endif