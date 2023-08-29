/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:41 by joppe             #+#    #+#             */
/*   Updated: 2023/08/28 17:08:38 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "plarser.h"
#include "utils.h"
#include "execute.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>


void cmd_free(t_cmd_list *cmd)
{
	str_free_2d(cmd->content.argv);
	free(cmd->content.infile);
	free(cmd->content.outfile);
	free(cmd);
}

int megashell(int argc, char *argv[], char *envp[])
{
	t_meta		meta;
	char		*line;
	t_cmd_list	*cmds;
	t_exec		execute;

	(void) argc;
	(void) argv;

	ft_bzero(&meta, sizeof(t_meta));
	prompt_env_setup();
	hs_read_history_file(HISTORY_FILE_NAME);
	if (search_path(&execute, envp) == EXIT_FAILURE)
			printf("error search path\n");
	while (!meta.stop)
	{
		line = prompt_get_line();
		if (!line)
		{
			printf("line is empty, exiting...\n");
			return (0);
		}
		cmds = plarser_main(line);
		print_cmds(cmds);
		execution(&execute, cmds);
		pr_lstiter(cmds, cmd_free);
		free(line);
	}

	return (0);
}
