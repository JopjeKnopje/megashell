/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:10:53 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 18:11:40 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "plarser.h"
#include <stdio.h>

bool handle_redir_input(t_cmd_frame *f)
{
	int fd;

	if (f->infile != NULL)
	{
		fd = open(f->infile, O_RDONLY);
		if (fd == -1)
		{
			print_error(strerror(errno));
			exit(errno);
		}
		dup_stdin(fd);
	}
	return (true);
}

bool handle_redir_output(t_cmd_frame *f)
{
	int fd;
	int flags;

	flags = O_WRONLY | O_CREAT;
	if (f->outfile != NULL)
	{
		if (f->is_append)
			flags |= O_APPEND; /* add O_APPEND: all write actions happen at EOF */
		else
			flags |= O_TRUNC; /* add O_TRUNC: write to EOF instead of overwrite start */
		fd = open(f->outfile, flags, 0644);
		if (fd == -1)
		{
			print_error(strerror(errno));
			exit(errno);
		}
		dup_stdout(fd);
	}
	return true;
}

bool redirections(t_cmd_frame *f)
{
	if (f->is_heredoc)
	{
		if (!handle_heredoc(f) || !handle_redir_output(f))
			return (false);
	}
	else
	{
		if (!handle_redir_input(f) || !handle_redir_output(f))
			return (false);
	}
	return (true);
}
