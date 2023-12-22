/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                  :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:32:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/23 00:32:05 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include "heredoc.h"
#include "execute.h"
#include "input.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	get_heredoc_exit_status(t_hd_list *heredoc_pipes)
{
	int	status;

	while (heredoc_pipes->next)
		heredoc_pipes = heredoc_pipes->next;
	status = heredoc_pipes->fd;
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (WEXITSTATUS(status));
}

void	pipeline_kill_nodes(t_cmd_list *cmds, t_cmd_list *end)
{
	while (cmds && cmds != end)
	{
		kill(cmds->pid, SIGKILL);
		close(cmds->pipe[PIPE_READ]);
		close(cmds->pipe[PIPE_WRITE]);
		cmds = cmds->next;
	}
}

int32_t	pop_heredoc(bool has_hd, t_hd_list **heredoc_pipes)
{
	int32_t		fd;
	t_hd_list	*first;

	fd = INTERNAL_FAILURE;
	if (has_hd)
	{
		first = hd_lstremove_first(heredoc_pipes);
		fd = first->fd;
		free(first);
	}
	return (fd);
}

int	run_multiple_cmds(t_meta *meta, t_cmd_list *cmds, t_cmd_list \
	*const cmds_head, t_hd_list **heredoc_pipes)
{
	while (cmds)
	{
		if (!pipeline_node(meta, cmds, \
			pop_heredoc(cmds->content.heredoc_delim != NULL, \
			heredoc_pipes)))
		{
			hd_lst_free(*heredoc_pipes);
			pipeline_kill_nodes(cmds_head, cmds);
			print_error(get_error_name(ERROR_PIPE));
			return (0);
		}
		cmds = cmds->next;
	}
	return (1);
}
