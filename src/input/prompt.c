/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:01 by joppe             #+#    #+#             */
/*   Updated: 2023/11/26 23:18:33 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>
#include "execute.h"
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

bool prompt_env_setup()
{
	if (!isatty(STDOUT_FILENO))
		return (false);
	// TODO Error handling.
	// sigals_setup();
	set_exit_code(0);
	disable_echoctl();
	return (true);
}

char *prompt_get_line()
{
	char	*line;
	
	while (1)
	{
		line = readline(SHELL_PROMPT);
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
