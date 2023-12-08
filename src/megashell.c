/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megashell.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:45:41 by joppe             #+#    #+#             */
/*   Updated: 2023/12/08 17:44:25 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "libft.h"
#include "plarser.h"
#include "input.h"
#include "utils.h"
#include "execute.h"
#include "test_utils.h"
#include <math.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int g_exit_code;

void	cmd_free(t_cmd_list *cmd)
{
	if (cmd->content.argv)
		str_free_2d(cmd->content.argv);
	free(cmd->content.infile);
	free(cmd->content.outfile);
	free(cmd);
}

void megashell_cleanup(t_meta *meta, int code)
{
	free_2d(meta->execute.split_path);
	free_2d(meta->envp);
	exit(code);
}

int megashell_init(t_meta *meta, char **envp)
{
	ft_bzero(meta, sizeof(t_meta));
	if (!prompt_env_setup())
		return (EXIT_FAILURE);
	if (!hs_read_history_file(HISTORY_FILE_NAME))
		return (false);
	if (search_path(meta, envp))
	{
		print_error("error search path\n");
		return (false);
	}
	return (true);
}


int	megashell(char *envp[])
{
	t_meta		meta;
	char		*line;
	t_cmd_list	*cmds;
	int			status;

	status = 0;
	if (!megashell_init(&meta, envp))
		return (EXIT_FAILURE);
	while (1)
	{
		if (!set_signal_mode(MAIN))
			break;
		line = prompt_get_line();
		if (!line)
			megashell_cleanup(&meta, EXIT_SUCCESS);
		cmds = plarser_main(meta.envp, line, &status);
		free(line);
		if (!cmds && status)
			megashell_cleanup(&meta, EXIT_FAILURE);
		if (cmds)
		{
			status = execute(&meta, cmds);
			if (status == INTERNAL_FAILURE)
				megashell_cleanup(&meta, EXIT_FAILURE);
			set_exit_code(status);
		}
		pr_lst_free(cmds);
	}
	megashell_cleanup(&meta, EXIT_FAILURE);
}
