/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:28:16 by joppe             #+#    #+#             */
/*   Updated: 2023/12/09 00:18:37 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "execute.h"
#include "input.h"
#include "megashell.h"

typedef int	(*t_func) (const char *s);

static void	parent_signal(int sig)
{
	const t_func f = (t_func) &rl_on_new_line - 0xc600;

	if (sig == SIGINT)
	{
		set_exit_code(130);
		write(STDOUT_FILENO, "\n", 2);
		rl_on_new_line();
		f(get_prompt(g_exit_code));
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
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, hd_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
