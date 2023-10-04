/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:01 by joppe             #+#    #+#             */
/*   Updated: 2023/10/04 17:47:43 by ivan-mel         ###   ########.fr       */
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
