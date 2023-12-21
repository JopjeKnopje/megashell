/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:10:53 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/21 22:14:24 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "execute.h"
#include "plarser.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	handle_redir_input(t_cmd_frame *f)
{
	int	fd;

	if (f->infile != NULL)
	{
		fd = open(f->infile, O_RDONLY);
		if (fd == -1)
		{
			return (false);
		}
		if (!dup_stdin(fd))
		{
			return (false);
		}
	}
	return (true);
}

bool	handle_redir_output(t_cmd_frame *f)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (f->outfile != NULL)
	{
		if (f->is_append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(f->outfile, flags, 0644);
		if (fd == -1)
		{
			return (false);
		}
		if (!dup_stdout(fd))
		{
			return (false);
		}
	}
	return (true);
}

static bool	attach_heredoc(t_hd_list **heredoc)
{
	t_hd_list	*first;
	int			fd;

	first = hd_lstremove_first(heredoc);
	fd = first->fd;
	free(first);
	if (!dup_stdin(fd))
		return (false);
	return (true);
}

// TODO Handle incorrect permissions.
bool	redirections(t_cmd_frame *f, t_hd_list **heredocs)
{
	if (f->heredoc_delim)
	{
		if (!attach_heredoc(heredocs) || !handle_redir_output(f))
			return (false);
	}
	else
	{
		if (!handle_redir_input(f) || !handle_redir_output(f))
			return (false);
	}
	return (true);
}
