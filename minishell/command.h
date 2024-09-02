/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:50:43 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/02 21:58:03 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

/* Possible values for command->flags. */
#define CMD_WANT_SUBSHELL  0x01	/* User wants a subshell: ( command ) */
#define CMD_FORCE_SUBSHELL 0x02	/* Shell needs to force a subshell. */
#define CMD_INVERT_RETURN  0x04	/* Invert the exit value. */
#define CMD_IGNORE_RETURN  0x08	/* Ignore the exit value.  For set -e. */
#define CMD_NO_FUNCTIONS   0x10 /* Ignore functions during command lookup. */
#define CMD_INHIBIT_EXPANSION 0x20 /* Do not expand the command words. */
#define CMD_NO_FORK	   0x40	/* Don't fork; just call execve */
#define CMD_TIME_PIPELINE  0x80 /* Time a pipeline */
#define CMD_TIME_POSIX	   0x100 /* time -p; use POSIX.2 time output spec. */
#define CMD_AMPERSAND	   0x200 /* command & */
#define CMD_STDIN_REDIR	   0x400 /* async command needs implicit </dev/null */
#define CMD_COMMAND_BUILTIN 0x0800 /* command executed by `command' builtin */
#define CMD_COPROC_SUBSHELL 0x1000
#define CMD_LASTPIPE	    0x2000
#define CMD_STDPATH	    0x4000	/* use standard path for command lookup */
#define CMD_TRY_OPTIMIZING  0x8000	/* try to optimize this simple command */

typedef struct command
{
	enum command_type type; /* FOR CASE WHILE IF CONNECTION or SIMPLE. */
	int flags;              /* Flags controlling execution environment. */
	int line;               /* line number the command starts on */
	REDIRECT *redirects;    /* Special redirects for FOR CASE, etc. */
	union
	{
		struct for_com			*For;
		struct case_com			*Case;
		struct while_com		*While;
		struct if_com			*If;
		struct connection		*Connection;
		struct simple_com		*Simple;
		struct function_def		*Function_def;
		struct group_com		*Group;
# if defined(SELECT_COMMAND)
		struct select_com		*Select;
# endif
# if defined(DPAREN_ARITHMETIC)
		struct arith_com		*Arith;
# endif
# if defined(COND_COMMAND)
		struct cond_com			*Cond;
# endif
# if defined(ARITH_FOR_COMMAND)
		struct arith_for_com	*ArithFor;
# endif
		struct subshell_com		*Subshell;
		struct coproc_com		*Coproc;
	} value;
}								COMMAND;

enum							command_type
{
	cm_for,
	cm_case,
	cm_while,
	cm_if,
	cm_simple,
	cm_select,
	cm_connection,
	cm_function_def,
	cm_until,
	cm_group,
	cm_arith,
	cm_cond,
	cm_arith_for,
	cm_subshell,
	cm_coproc
};

/* Structure describing a redirection.  If REDIRECTOR is negative, the parser
   (or translator in redir.c) encountered an out-of-range file descriptor. */
typedef struct redirect
{
	struct redirect *next; /* Next element, or NULL. */
	REDIRECTEE					redirector;
	/* Descriptor or varname to be redirected. */
	int rflags;                     /* Private flags for this redirection */
	int flags;                      /* Flag value for `open'. */
	enum r_instruction instruction; /* What to do with the information. */
	REDIRECTEE redirectee;          /* File descriptor or filename */
	char *here_doc_eof;             /* The word that appeared in <<foo. */
}								REDIRECT;

typedef union
{
	int dest;            /* Place to redirect REDIRECTOR to, or ... */
	WORD_DESC *filename; /* filename to redirect to. */
}								REDIRECTEE;

typedef struct word_desc
{
	char *word; /* Zero terminated string. */
	int flags;  /* Flags associated with this word. */
}								WORD_DESC;

enum							r_instruction
{
	r_output_direction,
	r_input_direction,
	r_inputa_direction,
	r_appending_to,
	r_reading_until,
	r_reading_string,
	r_duplicating_input,
	r_duplicating_output,
	r_deblank_reading_until,
	r_close_this,
	r_err_and_out,
	r_input_output,
	r_output_force,
	r_duplicating_input_word,
	r_duplicating_output_word,
	r_move_input,
	r_move_output,
	r_move_input_word,
	r_move_output_word,
	r_append_err_and_out
};

typedef struct subshell_com {
  int flags;
  int line;
  COMMAND *command;
} SUBSHELL_COM;

#endif