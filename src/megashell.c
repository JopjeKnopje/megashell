/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:41 by joppe             #+#    #+#             */
/*   Updated: 2023/08/29 10:33:09 by joppe         ########   odam.nl         */
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
	str_free_2d(cmd->content.argv);
	free(cmd->content.infile);
	free(cmd->content.outfile);
	free(cmd);
}

int megashell(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_cmd_list	*cmds;
	t_exec		execute;
	t_meta		meta;
	ft_bzero(&meta, sizeof(t_meta));

	meta.envp = envp;
	(void) argc;
	(void) argv;

	prompt_env_setup();
	hs_read_history_file(HISTORY_FILE_NAME);

	while (!meta.stop)
	{
		line = prompt_get_line();
		if (!line)
		{
			printf("line is empty, exiting...\n");
			return (0);
		}
		else if (!ft_strncmp(line, "test", ft_strlen("test")))
		{
			aliases_init(&meta);
		}
		else if (!ft_strncmp(line, "print", ft_strlen("print")))
		{
			printf("printing data bla bla\n");
			printf("printing data bla bla\n");
		}
		else if (!ft_strncmp(line, "exit", ft_strlen("exit")))
		{
			printf("exiting megashell\n");
			exit(0);
		}
		// cmds = plarser_main(line);
		// print_cmds(cmds);
		// if (search_path(&execute, envp) == EXIT_FAILURE)
		// {
		// 	printf("error searc path\n");
		// }
		// execution(&execute, cmds);


		// pr_lstiter(cmds, cmd_free);
		free(line);
	}

	return (0);
}
