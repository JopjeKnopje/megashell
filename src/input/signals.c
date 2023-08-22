/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:28:16 by joppe             #+#    #+#             */
/*   Updated: 2023/08/22 14:53:25 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigals_setup()
{
	struct sigaction act_int;
	struct sigaction act_quit;

	sigemptyset(&act_int.sa_mask);
	act_int.sa_handler = &signal_handler;
	act_int.sa_flags = SA_RESTART;

	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_handler = SIG_IGN;
	act_quit.sa_flags = 0;

	if (sigaction(SIGINT, &act_int, NULL) == -1)
	{
		
	}

	if (sigaction(SIGQUIT, &act_int, NULL) == -1)
	{

	}
}
