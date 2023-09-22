/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:41 by joppe             #+#    #+#             */
/*   Updated: 2023/09/22 22:31:52 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "libft.h"
#include "plarser.h"
#include "utils.h"
#include "execute.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cmd_free(t_cmd_list *cmd)
{
	if (cmd->content.argv)
		str_free_2d(cmd->content.argv);
	free(cmd->content.infile);
	free(cmd->content.outfile);
	free(cmd);
}

static void exit_shell(t_meta *meta)
{
	free_2d(meta->envp);
	exit(0);
}

int megashell(int argc, char *argv[], char *envp[])
{
	t_meta		meta;
	char		*line;
	t_cmd_list	*cmds;

	(void) argc;
	(void) argv;

	ft_bzero(&meta, sizeof(t_meta));
	prompt_env_setup();
	hs_read_history_file(HISTORY_FILE_NAME);
	if (search_path(&meta, envp) == EXIT_FAILURE)
		printf("error search path\n");
	while (! (!1))
	{
		line = prompt_get_line();
		if (!line || !strncmp(line, "x", ft_strlen(line)))
			exit_shell(&meta);

		cmds = plarser_main(&meta, line);
		print_cmds(cmds);
		if (cmds)
			execution(&meta, cmds);
		pr_lstiter(cmds, cmd_free);
		free(line);
	}
	return (0);
}
