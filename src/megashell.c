/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 15:45:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/07/31 17:19:19 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "input.h"
#include "libft.h"
#include "lexer.h"
#include <stdio.h>

int megashell(int argc, char *argv[], char *envp[])
{
	char *line;
	t_meta meta;

	ft_bzero(&meta, sizeof(t_meta));
	prompt_env_setup();
	while (!meta.stop)
	{
		line = prompt_get_line();
		lexer(line);
		free(line);
	}

	return (0);
}
