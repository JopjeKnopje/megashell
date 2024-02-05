/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:01 by joppe             #+#    #+#             */
/*   Updated: 2024/01/16 13:12:27 by jboeve        ########   odam.nl         */
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

bool	prompt_env_setup(void)
{
	if (!isatty(STDOUT_FILENO))
		return (false);
	set_exit_code(0);
	disable_echoctl();
	return (true);
}

const char	*get_prompt(int exit_code)
{
	if (!exit_code)
		return (SHELL_PROMPT);
	else
		return (SHELL_PROMPT_ERROR);
}

bool line_is_empty(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\v' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*prompt_get_line(void)
{
	char	*line;

	while (1)
	{
		line = readline(get_prompt(g_exit_code));
		if (line == NULL)
			return (NULL);
		if (line_is_empty(line))
		{
			free(line);
			continue ;
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
