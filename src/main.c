/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/24 12:00:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/25 12:27:11 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdatomic.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>
#include "libft.h"


typedef enum e_cmd_name {
	CMD_EXIT,
	CMD_CLEAR_HIS,
	CMD_COUNT,
} t_cmd_name;

static const char *BUILTINS[] = {
	"exit",
	"clear_his",
};


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
	while (1) 
	{
		char *line = readline("megashell> ");
		rl_insert_text("123");
		rl_redisplay();
		rl_on_new_line();
		if (ft_strisempty(line))
		{
			free(line);
			continue;
		}

		add_history(line);
		printf("line: [%s]\n", line);
		if (is_cmd(CMD_EXIT, line))
			exit(0);
		else if (is_cmd(CMD_CLEAR_HIS, line))
			rl_clear_history();
		free(line);
	}
	
	return 0;
}
