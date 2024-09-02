/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:12:06 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 20:00:32 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char											**export_env = (char **)NULL;
static int										export_env_index;

/* This is an efficiency hack.  PWD and OLDPWD are auto-exported, so
   we will need to remake the exported environment every time we
   change directories.  `_' is always put into the environment for
   every external command, so without special treatment it will always
   cause the environment to be remade.

   If there is no other reason to make the exported environment, we can
   just update the variables in place and mark the exported environment
   as no longer needing a remake. */
void											update_export_env_inplace(env_prefix,
												preflen,
												value) char *env_prefix;
int												preflen;
char											*value;
{
	char *evar;

	evar = (char *)xmalloc(STRLEN(value) + preflen + 1);
	strcpy(evar, env_prefix);
	if (value)
		strcpy(evar + preflen, value);
	export_env = add_or_supercede_exported_var(evar, 0);
}

/* Add ASSIGN to EXPORT_ENV, or supersede a previous assignment in the
   array with the same left-hand side.  Return the new EXPORT_ENV. */
char											**add_or_supercede_exported_var(assign,
												do_alloc) char *assign;
int												do_alloc;
{
	register int i;
	int equal_offset;

	equal_offset = assignment(assign, 0);
	if (equal_offset == 0)
		return (export_env);

	/* If this is a function, then only supersede the function definition.
		We do this by including the `=() {' in the comparison, like
		initialize_shell_variables does. */
	if (assign[equal_offset + 1] == '(' && strncmp(assign + equal_offset + 2,
			") {", 3) == 0) /* } */
		equal_offset += 4;

	for (i = 0; i < export_env_index; i++)
	{
		if (STREQN(assign, export_env[i], equal_offset + 1))
		{
			free(export_env[i]);
			export_env[i] = do_alloc ? savestring(assign) : assign;
			return (export_env);
		}
	}
	add_to_export_env(assign, do_alloc);
	return (export_env);
}

/* This is an efficiency hack.  PWD and OLDPWD are auto-exported, so
   we will need to remake the exported environment every time we
   change directories.  `_' is always put into the environment for
   every external command, so without special treatment it will always
   cause the environment to be remade.

   If there is no other reason to make the exported environment, we can
   just update the variables in place and mark the exported environment
   as no longer needing a remake. */
void											update_export_env_inplace(env_prefix,
												preflen,
												value) char *env_prefix;
int												preflen;
char											*value;
{
	char *evar;

	evar = (char *)xmalloc(STRLEN(value) + preflen + 1);
	strcpy(evar, env_prefix);
	if (value)
		strcpy(evar + preflen, value);
	export_env = add_or_supercede_exported_var(evar, 0); // type tis function for our needs and move it to main struct
}