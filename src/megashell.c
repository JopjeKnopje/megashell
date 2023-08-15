/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 15:45:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 23:56:44 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include <stdio.h>
#include <string.h>


// NOTE: All this stuff is for testing only should eventually be replaced with Iris's part.
#pragma region test

#include "lexer.h"

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


#pragma endregion test

int megashell(int argc, char *argv[], char *envp[])
{
	t_meta meta;
	t_tok_list *tokens;
	char *line;

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
		tokens = lx_main(line);
		pr_main(tokens);
		runner(line);
		lx_lst_free(tokens);
		free(line);
	}

	return (0);
}
