/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megashell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:41 by joppe             #+#    #+#             */
/*   Updated: 2023/11/22 17:07:53 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "libft.h"
#include "plarser.h"
#include "input.h"
#include "utils.h"
#include "execute.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


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
	signals_setup(MAIN);
	ft_bzero(&meta, sizeof(t_meta));
	if (!prompt_env_setup())
		return (EXIT_FAILURE);
	hs_read_history_file(HISTORY_FILE_NAME);
	if (search_path(&meta, envp) == EXIT_FAILURE)
		printf("error search path\n");
	while (1)
	{
		line = prompt_get_line();
		if (!line)
		{
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
