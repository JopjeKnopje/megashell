/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   prompt.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 15:45:01 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/19 11:40:06 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>
#include "libft.h"
#include "input.h"
#include "megashell.h"

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
		line = readline(READLINE_PROMPT);
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
