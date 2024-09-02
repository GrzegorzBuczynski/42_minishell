/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:43:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 18:47:26 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/* Execute a shell builtin or function in a subshell environment.  This
   routine does not return ; it only calls exit().  If BUILTIN is non-null,
   it points to a function to call to execute a shell builtin; otherwise
   VAR points at the body of a function to execute.  WORDS is the arguments
   to the command, REDIRECTS specifies redirections to perform before the
   command is executed. */
   // words, redirects, builtin, var, pipe_in, pipe_out, async,	fds_to_close,flags) 
static void	execute_subshell_builtin_or_function
(WORD_LIST *words, REDIRECT	*redirects, sh_builtin_func_t *builtin, SHELL_VAR *var, int pipe_in, 
int pipe_out, int async, struct fd_bitmap *fds_to_close, int flags)
WORD_LIST				*words;
REDIRECT				*redirects;
sh_builtin_func_t		*builtin;
SHELL_VAR				*var;
int pipe_in, pipe_out, async;
struct fd_bitmap		*fds_to_close;
int						flags;
{
	int result, r, funcvalue;
#if defined(JOB_CONTROL)
	int jobs_hack;

	jobs_hack = (builtin == jobs_builtin)
		&& ((subshell_environment & SUBSHELL_ASYNC) == 0
			|| pipe_out != NO_PIPE);
#endif

	/* A subshell is neither a login shell nor interactive. */
	login_shell = interactive = 0;
	if (builtin == eval_builtin)
		evalnest = 0;
	else if (builtin == source_builtin)
		sourcenest = 0;

	if (async)
		subshell_environment |= SUBSHELL_ASYNC;
	if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
		subshell_environment |= SUBSHELL_PIPE;

	maybe_make_export_env(); /* XXX - is this needed? */

#if defined(JOB_CONTROL)
	/* Eradicate all traces of job control after we fork the subshell, so
		all jobs begun by this subshell are in the same process group as
		the shell itself. */

	/* Allow the output of `jobs' to be piped. */
	if (jobs_hack)
		kill_current_pipeline();
	else
		without_job_control();

	set_sigchld_handler();
#else
	without_job_control();
#endif /* JOB_CONTROL */

	set_sigint_handler();

	if (fds_to_close)
		close_fd_bitmap(fds_to_close);

	do_piping(pipe_in, pipe_out);

	if (do_redirections(redirects, RX_ACTIVE) != 0)
		exit(EXECUTION_FAILURE);

	if (builtin)
	{
		/* Give builtins a place to jump back to on failure,
		so we don't go back up to main(). */
		result = setjmp_nosigs(top_level);

		/* Give the return builtin a place to jump to when executed in a subshell
			or pipeline */
		funcvalue = 0;
		if (return_catch_flag && builtin == return_builtin)
			funcvalue = setjmp_nosigs(return_catch);

		if (result == EXITPROG || result == EXITBLTIN)
			subshell_exit(last_command_exit_value);
		else if (result)
			subshell_exit(EXECUTION_FAILURE);
		else if (funcvalue)
			subshell_exit(return_catch_value);
		else
		{
			r = execute_builtin(builtin, words, flags, 1);
			fflush(stdout);
			if (r == EX_USAGE)
				r = EX_BADUSAGE;
			/* XXX - experimental */
			else if (r == EX_DISKFALLBACK)
			{
				char *command_line;

				command_line = savestring(the_printed_command_except_trap ? the_printed_command_except_trap : "");
				r = execute_disk_command(words, (REDIRECT *)0, command_line, -1,
						-1, async, (struct fd_bitmap *)0, flags | CMD_NO_FORK);
			}
			subshell_exit(r);
		}
	}
	else
	{
		r = execute_function(var, words, flags, fds_to_close, async, 1);
		fflush(stdout);
		subshell_exit(r);
	}
}

/* Execute a builtin or function in the current shell context.  If BUILTIN
   is non-null, it is the builtin command to execute, otherwise VAR points
   to the body of a function.  WORDS are the command's arguments, REDIRECTS
   are the redirections to perform.  FDS_TO_CLOSE is the usual bitmap of
   file descriptors to close.

   If BUILTIN is exec_builtin, the redirections specified in REDIRECTS are
   not undone before this function returns. */
static int				execute_builtin_or_function(words, builtin, var,
					redirects, fds_to_close, flags) WORD_LIST *words;
sh_builtin_func_t		*builtin;
SHELL_VAR				*var;
REDIRECT				*redirects;
struct fd_bitmap		*fds_to_close;
int						flags;
{
	int result;
	REDIRECT *saved_undo_list;
#if defined(PROCESS_SUBSTITUTION)
	int ofifo, nfifo, osize;
	void *ofifo_list;
#endif

#if defined(PROCESS_SUBSTITUTION)
	begin_unwind_frame("saved_fifos");
	/* If we return, we longjmp and don't get a chance to restore the old
		fifo list, so we add an unwind protect to free it */
	ofifo = num_fifos();
	ofifo_list = copy_fifo_list(&osize);
	if (ofifo_list)
		add_unwind_protect(xfree, ofifo_list);
#endif

	if (do_redirections(redirects, RX_ACTIVE | RX_UNDOABLE) != 0)
	{
		undo_partial_redirects();
		dispose_exec_redirects();
#if defined(PROCESS_SUBSTITUTION)
		free(ofifo_list);
#endif
		return (EX_REDIRFAIL); /* was EXECUTION_FAILURE */
	}

	saved_undo_list = redirection_undo_list;

	/* Calling the "exec" builtin changes redirections forever. */
	if (builtin == exec_builtin)
	{
		dispose_redirects(saved_undo_list);
		saved_undo_list = exec_redirection_undo_list;
		exec_redirection_undo_list = (REDIRECT *)NULL;
	}
	else
		dispose_exec_redirects();

	if (saved_undo_list)
	{
		begin_unwind_frame("saved-redirects");
		add_unwind_protect(cleanup_redirects, (char *)saved_undo_list);
	}

	redirection_undo_list = (REDIRECT *)NULL;

	if (builtin)
		result = execute_builtin(builtin, words, flags, 0);
	else
		result = execute_function(var, words, flags, fds_to_close, 0, 0);

	/* We do this before undoing the effects of any redirections. */
	fflush(stdout);
	fpurge(stdout);
	if (ferror(stdout))
		clearerr(stdout);

	/* If we are executing the `command' builtin, but this_shell_builtin is
		set to `exec_builtin', we know that we have something like
		`command exec [redirection]', since otherwise `exec' would have
		overwritten the shell and we wouldn't get here.  In this case, we
		want to behave as if the `command' builtin had not been specified
		and preserve the redirections. */
	if (builtin == command_builtin && this_shell_builtin == exec_builtin)
	{
		int discard;

		discard = 0;
		if (saved_undo_list)
		{
			dispose_redirects(saved_undo_list);
			discard = 1;
		}
		redirection_undo_list = exec_redirection_undo_list;
		saved_undo_list = exec_redirection_undo_list = (REDIRECT *)NULL;
		if (discard)
			discard_unwind_frame("saved-redirects");
	}

	if (saved_undo_list)
	{
		redirection_undo_list = saved_undo_list;
		discard_unwind_frame("saved-redirects");
	}

	undo_partial_redirects();

#if defined(PROCESS_SUBSTITUTION)
	/* Close any FIFOs created by this builtin or function. */
	nfifo = num_fifos();
	if (nfifo > ofifo)
		close_new_fifos(ofifo_list, osize);
	if (ofifo_list)
		free(ofifo_list);
	discard_unwind_frame("saved_fifos");
#endif

	return (result);
}

void	setup_async_signals(void)
{
#if defined(__BEOS__)
	set_signal_handler(SIGHUP, SIG_IGN); /* they want csh-like behavior */
#endif
#if defined(JOB_CONTROL)
	if (job_control == 0)
#endif
	{
		/* Make sure we get the original signal dispositions now so we don't
		confuse the trap builtin later if the subshell tries to use it to
		reset SIGINT/SIGQUIT.  Don't call set_signal_ignored; that sets
		the value of original_signals to SIG_IGN. Posix interpretation 751. */
		get_original_signal(SIGINT);
		set_signal_handler(SIGINT, SIG_IGN);
		get_original_signal(SIGQUIT);
		set_signal_handler(SIGQUIT, SIG_IGN);
	}
}

/* Execute a simple command that is hopefully defined in a disk file
   somewhere.

   1) fork ()
   2) connect pipes
   3) look up the command
   4) do redirections
   5) execve ()
   6) If the execve failed, see if the file has executable mode set.
   If so, and it isn't a directory, then execute its contents as
   a shell script.

   Note that the filename hashing stuff has to take place up here,
   in the parent.  This is probably why the Bourne style shells
   don't handle it, since that would require them to go through
   this gnarly hair, for no good reason.

   NOTE: callers expect this to fork or exit(). */

/* Name of a shell function to call when a command name is not found. */
#ifndef NOTFOUND_HOOK
# define NOTFOUND_HOOK "command_not_found_handle"
#endif

static int				execute_disk_command(words, redirects, command_line,
					pipe_in, pipe_out, async, fds_to_close,
					cmdflags) WORD_LIST *words;
REDIRECT				*redirects;
char					*command_line;
int pipe_in, pipe_out, async;
struct fd_bitmap		*fds_to_close;
int						cmdflags;
{
	char *pathname, *command, **args, *p;
	int nofork, stdpath, result, fork_flags;
	pid_t pid;
	SHELL_VAR *hookf;
	WORD_LIST *wl;

	stdpath = (cmdflags & CMD_STDPATH); /* use command -p path */
	nofork = (cmdflags & CMD_NO_FORK);  /* Don't fork, just exec, if no pipes */
	pathname = words->word->word;

	p = 0;
	result = EXECUTION_SUCCESS;
#if defined(RESTRICTED_SHELL)
	command = (char *)NULL;
	if (restricted && mbschr(pathname, '/'))
	{
		internal_error(_("%s: restricted: cannot specify `/' in command names"),
			pathname);
		result = last_command_exit_value = EXECUTION_FAILURE;

		/* If we're not going to fork below, we must already be in a child
			process or a context in which it's safe to call exit(2).  */
		if (nofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
			exit(last_command_exit_value);
		else
			goto parent_return ;
	}
#endif /* RESTRICTED_SHELL */

	/* If we want to change this so `command -p' (CMD_STDPATH) does not insert
		any pathname it finds into the hash table, it should read
		command = search_for_command (pathname,
				stdpath ? CMDSRCH_STDPATH : CMDSRCH_HASH);
	*/
	command = search_for_command(pathname,
			CMDSRCH_HASH | (stdpath ? CMDSRCH_STDPATH : 0));
	QUIT;

	if (command)
	{
		/* If we're optimizing out the fork (implicit `exec'), decrement the
		shell level like `exec' would do. Don't do this if we are already
		in a pipeline environment, assuming it's already been done. */
		if (nofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE
			&& (subshell_environment & SUBSHELL_PIPE) == 0)
			adjust_shell_level(-1);

		maybe_make_export_env();
		put_command_name_into_env(command);
	}

	/* We have to make the child before we check for the non-existence
		of COMMAND, since we want the error messages to be redirected. */
	/* If we can get away without forking and there are no pipes to deal with,
		don't bother to fork, just directly exec the command. */
	if (nofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
		pid = 0;
	else
	{
		fork_flags = async ? FORK_ASYNC : 0;
		pid = make_child(p = savestring(command_line), fork_flags);
	}

	if (pid == 0)
	{
		int old_interactive;

		reset_terminating_signals(); /* XXX */
		/* Cancel traps, in trap.c. */
		restore_original_signals();
		subshell_environment &= ~SUBSHELL_IGNTRAP;

#if defined(JOB_CONTROL)
		FREE(p);
#endif

		/* restore_original_signals may have undone the work done
		by make_child to ensure that SIGINT and SIGQUIT are ignored
		in asynchronous children. */
		if (async)
		{
			if ((cmdflags & CMD_STDIN_REDIR) && pipe_in == NO_PIPE
				&& (stdin_redirects(redirects) == 0))
				async_redirect_stdin();
			setup_async_signals();
		}

		/* This functionality is now provided by close-on-exec of the
		file descriptors manipulated by redirection and piping.
		Some file descriptors still need to be closed in all children
		because of the way bash does pipes; fds_to_close is a
		bitmap of all such file descriptors. */
		if (fds_to_close)
			close_fd_bitmap(fds_to_close);

		do_piping(pipe_in, pipe_out);

		old_interactive = interactive;
		if (async)
			interactive = 0;

		subshell_environment |= SUBSHELL_FORK; /* XXX - was just = */

#if defined(PROCESS_SUBSTITUTION) && !defined(HAVE_DEV_FD)
		clear_fifo_list(); /* XXX - we haven't created any FIFOs */
#endif

		/* reset shell_pgrp to pipeline_pgrp here for word expansions performed
			by the redirections here? */
		if (redirects && (do_redirections(redirects, RX_ACTIVE) != 0))
		{
#if defined(PROCESS_SUBSTITUTION)
			/* Try to remove named pipes that may have been created as the
				result of redirections. */
			unlink_all_fifos();
#endif /* PROCESS_SUBSTITUTION */
			exit(EXECUTION_FAILURE);
		}

#if defined(PROCESS_SUBSTITUTION) && !defined(HAVE_DEV_FD)
		/* This should only contain FIFOs created as part of redirection
		expansion. */
		unlink_all_fifos();
#endif

		if (async)
			interactive = old_interactive;

		if (command == 0)
		{
			hookf = find_function(NOTFOUND_HOOK);
			if (hookf == 0)
			{
				/* Make sure filenames are displayed using printable characters */
				pathname = printable_filename(pathname, 0);
				internal_error(_("%s: command not found"), pathname);
				exit(EX_NOTFOUND); /* Posix.2 says the exit status is 127 */
			}

			/* We don't want to manage process groups for processes we start
				from here, so we turn off job control and don't attempt to
				manipulate the terminal's process group. */
			without_job_control();

#if defined(JOB_CONTROL)
			set_sigchld_handler();
#endif

			wl = make_word_list(make_word(NOTFOUND_HOOK), words);
			exit(execute_shell_function(hookf, wl));
		}

		/* Execve expects the command name to be in args[0].  So we
		leave it there, in the same format that the user used to
		type it in. */
		args = strvec_from_word_list(words, 0, 0, (int *)NULL);
		exit(shell_execve(command, args, export_env));
	}
	else
	{
	parent_return:
		QUIT;

		/* Make sure that the pipes are closed in the parent. */
		close_pipes(pipe_in, pipe_out);
#if defined(PROCESS_SUBSTITUTION) && defined(HAVE_DEV_FD)
# if 0
      if (variable_context == 0)
        unlink_fifo_list ();
# endif
#endif

		FREE(command);
		return (result);
	}
}

static void	close_pipes(int in, int out)
{
	if (in >= 0)
		close(in);
	if (out >= 0)
		close(out);
}

static void	dup_error(int oldd, int newd)
{
	sys_error(_("cannot duplicate fd %d to fd %d"), oldd, newd);
}

/* Redirect input and output to be from and to the specified pipes.
   NO_PIPE and REDIRECT_BOTH are handled correctly. */
static void	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != NO_PIPE)
	{
		if (dup2(pipe_in, 0) < 0)
			dup_error(pipe_in, 0);
		if (pipe_in > 0)
			close(pipe_in);
	}
}