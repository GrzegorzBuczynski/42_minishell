/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:58:11 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/06 18:58:36 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(STDERR_FILENO, "  \b\b", 4);
}

void	init_signals(void)
{
	signal(SIGQUIT, signal_quit);
	signal(SIGINT, sig_handler);
}

void	sig_kill(int signum)
{
	signal(signum, SIG_IGN);
	kill(0, signum);
	if (signum == SIGQUIT)
		printf("Quit");
	printf("\n");
	rl_on_new_line();
}
