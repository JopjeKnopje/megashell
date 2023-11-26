/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:28:16 by joppe             #+#    #+#             */
/*   Updated: 2023/11/26 22:42:43 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "input.h"

extern int g_signal_num;

static void	parent_signal(int sig)
{
	if (sig == SIGINT)
	{
		// g_signal_num = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// else
	// 	g_signal_num = 131;
}

// static void	child_signal(int sig)
// {
// 	if (sig == SIGQUIT)
// 		g_signal_num = 131;
// 	else if (sig == SIGINT)
// 		g_signal_num = 130;
// }

// static void	hd_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		exit(130);
// 	}
// }

void	signals_setup(int mode)
{
	if (mode == MAIN)
	{
		signal(SIGINT, parent_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, parent_signal);
		signal(SIGQUIT, parent_signal);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
