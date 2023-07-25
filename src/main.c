/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/24 12:00:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/25 15:25:56 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include <stdbool.h>


typedef enum e_cmd_name {
	CMD_EXIT,
	CMD_CLEAR_HIS,
	CMD_COUNT,
} t_cmd_name;

static const char *BUILTINS[] = {
	"exit",
	"clear_his",
};



void handler(int sig)
{
    printf("\n");
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}

// void	init_shell_envioment(void)
// {
// 	struct termios	attributes;
// 	tcgetattr(STDIN_FILENO, &attributes);
// 	attributes.c_lflag &= ~(ECHOCTL);
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
// }

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
	signal(SIGINT, &handler);


	while (1) 
	{
		char *line = readline("megashell> ");
		if (line == NULL)
		{
			printf("ctrl-d\n");
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
