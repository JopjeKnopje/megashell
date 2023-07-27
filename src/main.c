/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/24 12:00:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/27 13:47:53 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include <stdbool.h>
#include <termios.h>

typedef enum e_cmd_name {
	CMD_EXIT,
	CMD_CLEAR_HIS,
	CMD_COUNT,
} t_cmd_name;

static const char *BUILTINS[] = {
	"exit",
	"clear_his",
};



void	set_termios(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGUSR1)
	{
		printf("got the siggie\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

bool is_cmd(t_cmd_name c, char *s)
{
	const char *cmd = BUILTINS[c];
	size_t len = strlen(s);
	if (len < strlen(cmd))
		len = strlen(cmd);
	return (!ft_strncmp(cmd, s, len));
}

int main(int argc, char *argv[])
{
	set_termios();

	struct sigaction act_int;
	struct sigaction act_quit;
	struct sigaction act_usr1;

	sigemptyset(&act_int.sa_mask);
	act_int.sa_flags = SA_RESTART;
	act_int.sa_handler = &signal_handler;


	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = 0;
	act_quit.sa_handler = SIG_IGN;

	sigemptyset(&act_usr1.sa_mask);
	act_usr1.sa_flags = SA_RESTART;
	act_usr1.sa_handler = &signal_handler;

	printf("pid: %d\n", getpid());


	sigaction(SIGINT, &act_int, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
	sigaction(SIGUSR1, &act_usr1, NULL);


	while (1) 
	{
		char *line = readline("megashell> ");
		if (line == NULL)
		{
			exit(0);
			continue;
		}
		else if (ft_strisempty(line))
		{
			free(line);
			continue;
		}
		printf("line [%s]\n", line);

		if (is_cmd(CMD_EXIT, line))
			exit(0);
		else if (is_cmd(CMD_CLEAR_HIS, line))
			rl_clear_history();
		free(line);
	}
	return 0;
}
