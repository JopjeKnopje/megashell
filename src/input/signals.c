/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:28:16 by joppe             #+#    #+#             */
/*   Updated: 2023/12/14 02:07:55 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "execute.h"
#include "input.h"
#include "megashell.h"

int	g_exit_code;

static void	parent_signal(int sig)
{
	if (sig == SIGINT)
	{
		set_exit_code(130);
		printf("\x1B[K");
		printf("%s", get_prompt(g_exit_code));
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	hd_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(130);
	}
}

bool	set_signal_mode(int mode)
{
	if (mode == MAIN)
		return (!(signal(SIGINT, parent_signal) == SIG_ERR \
				|| signal(SIGQUIT, SIG_IGN) == SIG_ERR));
	else if (mode == CHILD)
		return (!(signal(SIGINT, parent_signal) == SIG_ERR \
				|| signal(SIGQUIT, SIG_DFL) == SIG_ERR));
	else if (mode == HEREDOC)
		return (!(signal(SIGINT, hd_handler) == SIG_ERR \
				|| signal(SIGQUIT, SIG_IGN) == SIG_ERR));
	else if (mode == IGNORE)
		return (!(signal(SIGINT, SIG_IGN) == SIG_ERR \
				|| signal(SIGQUIT, SIG_IGN) == SIG_ERR));
	return (true);
}
