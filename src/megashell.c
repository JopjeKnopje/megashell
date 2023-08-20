/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 15:45:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 23:36:55 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "plarser.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>


// NOTE: All this stuff is for testing only should eventually be replaced with Iris's part.
#pragma region test


static void builtin_exit()
{
	exit(0);
}

static void builtin_clear()
{
	printf("\033[2J");
	printf("\033[H");
}

typedef enum e_builtin {
	BUILTIN_EXIT,
	BUILTIN_CLEAR,
	BUILTIN_COUNT,
}	t_builtin;

static const char *BUILTIN_NAMES[] = {
	"x",
	"c",
};

void (*BUILTIN_FUNCS[2])(void) = {
	builtin_exit,
	builtin_clear,
};


bool is_cmd(const char *name, char *s)
{
	size_t len = strlen(s);
	if (len < strlen(name))
		len = strlen(name);
	return (!ft_strncmp(name, s, len));
}

static void runner(char *s)
{
	uint32_t i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (is_cmd(BUILTIN_NAMES[i], s))
			(*BUILTIN_FUNCS[i])();
		i++;
	}
}

void cmd_free(t_cmd_list *cmd)
{
	str_free_2d(cmd->content.argv);
	free(cmd);
}

#pragma endregion test



int megashell(int argc, char *argv[], char *envp[])
{
	t_meta		meta;
	char		*line;
	t_cmd_list	*cmds;

	(void) argc;
	(void) argv;
	(void) envp;

	ft_bzero(&meta, sizeof(t_meta));
	prompt_env_setup();
	hs_read_history_file(HISTORY_FILE_NAME);
	while (!meta.stop)
	{
		line = prompt_get_line();
		if (!line)
		{
			printf("line is empty, exiting...\n");
			return (0);
		}
		cmds = plarser_main(line);
		runner(line);


		pr_lstiter(cmds, cmd_free);
		free(line);
	}

	return (0);
}
