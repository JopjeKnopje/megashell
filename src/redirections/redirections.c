/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:10:53 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/22 16:07:01 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "execute.h"
#include "plarser.h"
#include <fcntl.h>
#include <stdint.h>
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

static bool	attach_heredoc(int32_t heredoc_fd)
{
	if (!dup_stdin(heredoc_fd))
		return (false);
	return (true);
}

// TODO Handle incorrect permissions.
bool	redirections(t_cmd_frame *f, int32_t heredoc_fd)
{
	if (f->heredoc_delim)
	{
		fprintf(stderr, "running heredoc [%ld]\n", f->index);
		if (!attach_heredoc(heredoc_fd) || !handle_redir_output(f))
			return (false);
	}
	else
	{
		if (!handle_redir_input(f) || !handle_redir_output(f))
			return (false);
	}
	return (true);
}
