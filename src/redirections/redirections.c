/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:10:53 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/23 15:02:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "plarser.h"
#include <stdio.h>

t_cmd_frame	*handle_redir_input(t_cmd_list *cmd_list)
{
	t_cmd_list	*current_cmd;
	t_cmd_frame	*cmd_frame;
	int			fd;


	current_cmd = cmd_list;
	cmd_frame = &current_cmd->content;
	if (cmd_frame->is_heredoc)
	{
		printf("is a heredoc\n");
		handle_heredoc(cmd_frame);
		return (cmd_frame);
	}
	if (cmd_frame->infile != NULL)
	{
		fd = open(cmd_frame->infile, O_RDONLY);
		if (fd == -1)
		{
			print_error(strerror(errno));
			exit(errno);
		}
		else
			dup_stdin(fd);
	}
	return (cmd_frame);
}

void	handle_redir_output(t_cmd_frame *cmd_frame)
{
	int	fd;
	int	flags;


	fprintf(stderr, "handle_redir_output cmd: [%s]\n", cmd_frame->argv[0]);
	flags = O_WRONLY | O_CREAT;
	if (cmd_frame->outfile != NULL)
	{
		if (cmd_frame->is_append)
			flags |= O_APPEND; /* add O_APPEND: all write actions happen at EOF */
		else
			flags |= O_TRUNC; /* add O_TRUNC: write to EOF instead of overwrite start */
		fd = open(cmd_frame->outfile, flags, 0644);
		if (fd == -1)
		{
			print_error(strerror(errno));
			exit(errno);
		}
		else
			dup_stdout(fd);
	}
}

void	redirects(t_cmd_list *cmd_list)
{
	t_cmd_frame	*cmd_frame;

	cmd_frame = handle_redir_input(cmd_list);
	if (cmd_frame->is_heredoc)
		return ;
	handle_redir_output(cmd_frame);
}
