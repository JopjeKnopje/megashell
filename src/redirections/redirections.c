/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:10:53 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/06 18:03:59 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "plarser.h"

t_cmd_frame	*handle_redir_input(t_cmd_list *cmd_list)
{
	t_cmd_list	*current_cmd;
	t_cmd_frame	*cmd_frame;
	int			fd;

	current_cmd = cmd_list;
	printf("test1\n");
	while (current_cmd != NULL)
	{
		cmd_frame = &current_cmd->content;
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
		// else if (cmd_frame->is_heredoc)
		// 	handle_heredoc()
		current_cmd = current_cmd->next;
	}
	return (cmd_frame);
}

void	handle_redir_output(t_cmd_frame *cmd_frame)
{
	int	fd;
	int	flags;

	printf("test2\n");
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

	printf("check\n");
	cmd_frame = handle_redir_input(cmd_list);
	handle_redir_output(cmd_frame);
}