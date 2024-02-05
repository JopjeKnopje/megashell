/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:06:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/02/04 22:01:35 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include "libft.h"
#include "input.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

uint8_t	read_from_heredoc(t_meta *meta, char *close_line, int pipe_fd)
{
	char	*line;
	char	*exp_line;

	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			break ;
		if (!ft_strncmp(line, close_line, ft_strlen(close_line) + 1))
		{
			free(line);
			break ;
		}
		exp_line = hd_exp(meta, line);
		write(pipe_fd, exp_line, strlen(exp_line) + 1);
		write(pipe_fd, "\n", 1);
		free (exp_line);
	}
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_meta *meta, t_cmd_frame *f, int *status)
{
	int		pipe_fd[2];
	int		pid;
	uint8_t	child_exit_code;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_signal_mode(HEREDOC);
		close (pipe_fd[PIPE_READ]);
		child_exit_code = read_from_heredoc \
			(meta, f->heredoc_delim, pipe_fd[PIPE_WRITE]);
		close (pipe_fd[PIPE_WRITE]);
		exit(child_exit_code);
	}
	close(pipe_fd[PIPE_WRITE]);
	waitpid(pid, status, 0);
	return (pipe_fd[PIPE_READ]);
}

t_hd_list	*append_heredoc(t_hd_list **head, int heredoc_fd)
{
	t_hd_list	*tmp;

	tmp = hd_lstnew(heredoc_fd);
	if (!tmp)
		return (NULL);
	hd_lstadd_back(head, tmp);
	return (*head);
}

bool	contains_heredoc(t_cmd_list *cmds)
{
	while (cmds)
	{
		if (cmds->content.heredoc_delim)
			return (true);
		cmds = cmds->next;
	}
	return (false);
}

t_hd_list	*run_heredocs(t_meta *meta, t_cmd_list *cmds)
{
	t_hd_list	*head;
	int			fd;
	int			status;

	head = NULL;
	if (!set_signal_mode(IGNORE))
		return (NULL);
	while (cmds)
	{
		if (cmds->content.heredoc_delim)
		{
			fd = handle_heredoc(meta, &cmds->content, &status);
			if (fd == -1 || !append_heredoc(&head, fd))
			{
				hd_lst_free(head);
				return (NULL);
			}
		}
		cmds = cmds->next;
	}
	append_heredoc(&head, status);
	return (head);
}
