/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   prompt.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 15:45:01 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/04 19:17:14 by jboeve        ########   odam.nl         */
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
	char *line;
	
	while (1)
	{
		line = readline("megashell> ");
		if (line == NULL)
			exit(0);
		else if (ft_strisempty(line))
		{
			free(line);
			continue;
		}
		add_history(line);
		return (line);
	}
}
