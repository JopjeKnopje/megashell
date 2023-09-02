/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   prompt.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 15:45:01 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/02 21:48:40 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>
#include "libft.h"
#include "input.h"

static void	disable_echoctl(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

void prompt_env_setup()
{
	sigals_setup();
	// disable_echoctl();
}

char *prompt_get_line()
{
	char	*line;
	
	while (1)
	{
		printf("\x1b[0m");
		line = readline("megashell> ");
		if (line == NULL)
			return (NULL);
		if (ft_strisempty(line))
		{
			free(line);
			continue;
		}
		add_history(line);
		hs_add_history_file(HISTORY_FILE_NAME, line);
		return (line);
	}
}
