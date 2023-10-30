/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:41 by joppe             #+#    #+#             */
/*   Updated: 2023/10/30 19:32:48 by joppe         ########   odam.nl         */
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
#include <sys/wait.h>


void	cmd_free(t_cmd_list *cmd)
{
	if (cmd->content.argv)
		str_free_2d(cmd->content.argv);
	free(cmd->content.infile);
	free(cmd->content.outfile);
	free(cmd);
}

void megashell_cleanup(t_meta *meta)
{
	free_2d(meta->execute.split_path);
	free_2d(meta->envp);
}

int	megashell(int argc, char *argv[], char *envp[])
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
	while (1)
	{
		line = prompt_get_line();
		if (!line)
		{
			printf("line is empty, exiting...\n");
			megashell_cleanup(&meta);
			return (0);
		}
		cmds = plarser_main(meta.envp, line);
		if (cmds)
		{
			print_cmds(cmds);
			execute(&meta, cmds);
		}
		pr_lst_free(cmds);
		free(line);
	}
	return (0);
}
