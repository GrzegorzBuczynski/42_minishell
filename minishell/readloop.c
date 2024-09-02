/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:53:49 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/01 19:42:38 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

COMMAND	*global_command;

int indirection_level = 0;
int just_one_command = 0;
int EOF_Reached = 0;

reader_loop()
{
	int		our_indirection_level;
	int		code;
	char	*ps0_string;

	COMMAND *volatile current_command;
	USE_VAR(current_command);
	current_command = (COMMAND *)NULL;
	our_indirection_level = ++indirection_level;
	if (just_one_command)
		reset_readahead_token();
	while (EOF_Reached == 0)
	{
		code = setjmp_nosigs(0); //top_level
#if defined(PROCESS_SUBSTITUTION)
		unlink_fifo_list();
#endif /* PROCESS_SUBSTITUTION */
		/* XXX - why do we set this every time through the loop?  And why do
		it if SIGINT is trapped in an interactive shell? */
		if (interactive_shell && signal_is_ignored(SIGINT) == 0
			&& signal_is_trapped(SIGINT) == 0)
			set_signal_handler(SIGINT, sigint_sighandler);
		if (code != NOT_JUMPED)
		{
			indirection_level = our_indirection_level;
			switch (code)
			{
				/* Some kind of throw to top_level has occurred. */
			case ERREXIT:
				if (exit_immediately_on_error)
					reset_local_contexts(); /* not in a function */
			case FORCE_EOF:
			case EXITPROG:
			case EXITBLTIN:
				current_command = (COMMAND *)NULL;
				EOF_Reached = EOF;
				goto exec_done;
			case DISCARD:
				/* Make sure the exit status is reset to a non-zero value, but
				leave existing non-zero values (e.g., > 128 on signal)
				alone. */
				if (last_command_exit_value == 0)
					set_exit_status(EXECUTION_FAILURE);
				if (subshell_environment)
				{
					current_command = (COMMAND *)NULL;
					EOF_Reached = EOF;
					goto exec_done;
				}
				/* Obstack free command elements, etc. */
				if (current_command)
				{
					dispose_command(current_command);
					current_command = (COMMAND *)NULL;
				}
				restore_sigmask();
				break ;
			default:
				command_error("reader_loop", CMDERR_BADJUMP, code, 0);
			}
		}
		executing = 0;
		if (temporary_env)
			dispose_used_env_vars();
#if (defined(ultrix) && defined(mips)) || defined(C_ALLOCA)
		/* Attempt to reclaim memory allocated with alloca (). */
		(void)alloca(0);
#endif
		if (read_command() == 0)
		{
			if (interactive_shell == 0 && read_but_dont_execute)
			{
				set_exit_status(last_command_exit_value);
				dispose_command(global_command);
				global_command = (COMMAND *)NULL;
			}
			else if (current_command = global_command)
			{
				global_command = (COMMAND *)NULL;
				/* If the shell is interactive,
					expand and display $PS0 after reading a
				command (possibly a list or pipeline) and before executing it. */
				if (interactive && ps0_prompt)
				{
					ps0_string = decode_prompt_string(ps0_prompt);
					if (ps0_string && *ps0_string)
					{
						fprintf(stderr, "%s", ps0_string);
						fflush(stderr);
					}
					free(ps0_string);
				}
				current_command_number++;
				executing = 1;
				stdin_redir = 0;
				execute_command(current_command);
			exec_done:
				QUIT;
				if (current_command)
				{
					dispose_command(current_command);
					current_command = (COMMAND *)NULL;
				}
			}
		}
		else
		{
			/* Parse error, maybe discard rest of stream if not interactive. */
			if (interactive == 0)
				EOF_Reached = EOF;
		}
		if (just_one_command)
			EOF_Reached = EOF;
	}
	indirection_level--;
	return (last_command_exit_value);
}

/* Read and parse a command, returning the status of the parse.  The command
   is left in the globval variable GLOBAL_COMMAND for use by reader_loop.
   This is where the shell timeout code is executed. */
int	read_command(void)
{
	SHELL_VAR	*tmout_var;
	SigHandler	*old_alrm;

	int tmout_len, result;
	set_current_prompt_level(1);
	global_command = (COMMAND *)NULL;
	/* Only do timeouts if interactive. */
	tmout_var = (SHELL_VAR *)NULL;
	tmout_len = 0;
	old_alrm = (SigHandler *)NULL;
	if (interactive)
	{
		tmout_var = find_variable("TMOUT");
		if (tmout_var && var_isset(tmout_var))
		{
			tmout_len = atoi(value_cell(tmout_var));
			if (tmout_len > 0)
			{
				old_alrm = set_signal_handler(SIGALRM, alrm_catcher);
				alarm(tmout_len);
			}
		}
	}
	QUIT;
	current_command_line_count = 0;
	result = parse_command();
	if (interactive && tmout_var && (tmout_len > 0))
	{
		alarm(0);
		set_signal_handler(SIGALRM, old_alrm);
	}
	return (result);
}
