/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:01 by joppe             #+#    #+#             */
/*   Updated: 2023/12/11 16:02:48 by ivan-mel         ###   ########.fr       */
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

bool	prompt_env_setup()
{
	if (!isatty(STDOUT_FILENO))
		return (false);
	set_exit_code(0);
	disable_echoctl();
	return (true);
}

const char *get_prompt(int exit_code)
{
	if (!exit_code)
		return SHELL_PROMPT;
	else
		return SHELL_PROMPT_ERROR;
}

char *prompt_get_line()
{
	char	*line;
	
	while (1)
	{
		line = readline(get_prompt(g_exit_code));
		if (line == NULL)
			return (NULL);
		if (ft_strisempty(line))
		{
			free(line);
			continue;
		}
		add_history(line);
		if (!hs_add_history_file(HISTORY_FILE_NAME, line))
		{
			print_error(strerror(errno));
			return (NULL);
		}
		return (line);
	}
}
