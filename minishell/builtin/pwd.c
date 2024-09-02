/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:04:15 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 21:31:38 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

setpwd(char *dirname)
{
	int			old_anm;
	SHELL_VAR	*tvar;

	old_anm = array_needs_making;
	tvar = bind_variable("PWD", dirname ? dirname : "", 0);
	if (tvar && readonly_p(tvar))
		return (EXECUTION_FAILURE);
	if (tvar && old_anm == 0 && array_needs_making && exported_p(tvar))
	{
		update_export_env_inplace("PWD=", 4, dirname ? dirname : "");
		array_needs_making = 0;
	}
	return (EXECUTION_SUCCESS);
}

static int		bindpwd(no_symlinks) int no_symlinks;
{
	char *dirname, *pwdvar;
	int old_anm, r, canon_failed;
	SHELL_VAR *tvar;

	r = sh_chkwrite(EXECUTION_SUCCESS);

#define tcwd the_current_working_directory
	dirname = tcwd ? (no_symlinks ? sh_physpath(tcwd,
				0) : tcwd) : get_working_directory("cd");
#undef tcwd

	/* If canonicalization fails,
		reset dirname to the_current_working_directory */
	canon_failed = 0;
	if (dirname == 0)
	{
		canon_failed = 1;
		dirname = the_current_working_directory;
	}

	old_anm = array_needs_making;
	pwdvar = get_string_value("PWD");

	tvar = bind_variable("OLDPWD", pwdvar, 0);
	if (tvar && readonly_p(tvar))
		r = EXECUTION_FAILURE;

	if (old_anm == 0 && array_needs_making && exported_p(tvar))
	{
		update_export_env_inplace("OLDPWD=", 7, pwdvar);
		array_needs_making = 0;
	}

	if (setpwd(dirname) == EXECUTION_FAILURE)
		r = EXECUTION_FAILURE;
	if (canon_failed && eflag)
		r = EXECUTION_FAILURE;

	if (dirname && dirname != the_current_working_directory)
		free(dirname);

	return (r);
}

// #include "../bashansi.h"

// #include "../shell.h"
// #include "../execute_cmd.h"
// #include "../flags.h"
// #include "bashgetopt.h"
// #include "common.h"

// #if defined (_CS_PATH) && defined (HAVE_CONFSTR) && !HAVE_DECL_CONFSTR
// extern size_t confstr PARAMS((int, char *, size_t));
// #endif

/* Run the commands mentioned in LIST without paying attention to shell
   functions. */

#define COMMAND_BUILTIN_FLAGS (CMD_NO_FUNCTIONS | CMD_INHIBIT_EXPANSION | CMD_COMMAND_BUILTIN | (use_standard_path ? CMD_STDPATH : 0))
{
//   INTERNAL_DEBUG (("command_builtin: running execute_command for `%s'", list->word->word));

  /* We don't want this to be reparsed (consider command echo 'foo &'), so
     just make a simple_command structure and call execute_command with it. */
  command = make_bare_simple_command ();
  command->value.Simple->words = (WORD_LIST *)copy_word_list (list);
  command->value.Simple->redirects = (REDIRECT *)NULL;
  command->flags |= COMMAND_BUILTIN_FLAGS;
  command->value.Simple->flags |= COMMAND_BUILTIN_FLAGS;

  add_unwind_protect ((char *)dispose_command, command);
  result = execute_command (command);

  run_unwind_frame ("command_builtin");

  return (result);
}




WORD_LIST *loptend; /* Points to the first non-option argument in the list */

int	command_builtin(WORD_LIST *list)
{
	COMMAND	*command;

	int result, verbose, use_standard_path, opt;
	verbose = use_standard_path = 0;
	// reset_internal_getopt();
	// while ((opt = internal_getopt(list, "pvV")) != -1)
	// {
	// 	switch (opt)
	// 	{
	// 	case 'p':
	// 		use_standard_path = CDESC_STDPATH;
	// 		break ;
	// 	case 'V':
	// 		verbose = CDESC_SHORTDESC | CDESC_ABSPATH;
	// 			/* look in common.h for constants */
	// 		break ;
	// 	case 'v':
	// 		verbose = CDESC_REUSABLE; /* ditto */
	// 		break ;
	// 		CASE_HELPOPT;
	// 	default:
	// 		builtin_usage();
	// 		return (EX_USAGE);
	// 	}
	// }
	// list = loptend;
	// if (list == 0)
	// 	return (EXECUTION_SUCCESS);
	// #if defined(RESTRICTED_SHELL)
	// 	if (use_standard_path && restricted)
	// 	{
	// 		sh_restricted("-p");
	// 		return (EXECUTION_FAILURE);
	// 	}
	// #endif
	// if (verbose)
	// {
	// 	int found, any_found;
	// 	for (any_found = 0; list; list = list->next)
	// 	{
	// 		found = describe_command(list->word->word,
	// 				verbose | use_standard_path);
	// 		if (found == 0 && verbose != CDESC_REUSABLE)
	// 			sh_notfound(list->word->word);
	// 		any_found += found;
	// 	}
	// 	return (any_found ? EXECUTION_SUCCESS : EXECUTION_FAILURE);
	// }
	// begin_unwind_frame("command_builtin");
#define COMMAND_BUILTIN_FLAGS (CMD_NO_FUNCTIONS | CMD_INHIBIT_EXPANSION | CMD_COMMAND_BUILTIN | (use_standard_path ? CMD_STDPATH : 0))
	// INTERNAL_DEBUG(("command_builtin: running execute_command for `%s'",
	// 		list->word->word));
	/* We don't want this to be reparsed (consider command echo 'foo &'), so
		just make a simple_command structure and call execute_command with it. */
	command = make_bare_simple_command();
	command->value.Simple->words = (WORD_LIST *)copy_word_list(list);
	command->value.Simple->redirects = (REDIRECT *)NULL;
	command->flags |= COMMAND_BUILTIN_FLAGS;
	command->value.Simple->flags |= COMMAND_BUILTIN_FLAGS;
	// add_unwind_protect((char *)dispose_command, command);
	result = execute_command(command);
	// run_unwind_frame("command_builtin");
	return (result);
}

typedef void	VFunction(char *arg1, char *arg2);
// unwind_prot.c 114
static void	without_interrupts(VFunction *function, char *arg1, char *arg2)
{
	(*function)(arg1, arg2);
}