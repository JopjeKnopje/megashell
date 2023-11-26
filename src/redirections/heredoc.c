/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:06:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/11/26 20:45:42 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "execute.h"
#include "plarser.h"
#include "libft.h"
#include "input.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

uint8_t	read_from_heredoc(char *close_line, int pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			{
				break;
			}
		if (!ft_strncmp(line, close_line, ft_strlen(close_line) + 1))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, strlen(line) + 1);
		write(pipe_fd, "\n", 1);
		free (line);
	}
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_cmd_frame *f)
{
	int		pipe_fd[2];
	int		pid;
	int		status;
	uint8_t	child_exit_code;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signals_setup(HEREDOC);
		close (pipe_fd[PIPE_READ]);
		child_exit_code = read_from_heredoc(f->heredoc_delim, pipe_fd[PIPE_WRITE]);
		close (pipe_fd[PIPE_WRITE]);
		exit(child_exit_code);
	}
	close(pipe_fd[PIPE_WRITE]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (-1);
	
	// child_exit_code = WEXITSTATUS(status);
	// dprintf(STDERR_FILENO, "child_exit %d\n", child_exit_code);
	return (pipe_fd[PIPE_READ]);
}

static t_hd_list *append_heredoc(t_hd_list **head, int heredoc_fd)
{
	t_hd_list *tmp;

	tmp = hd_lstnew(heredoc_fd);
	if (!tmp)
		return (NULL);
	hd_lstadd_back(head, tmp);
	return (*head);
}

bool contains_heredoc(t_cmd_list *cmds)
{
	while (cmds)
	{
		if (cmds->content.heredoc_delim)
			return (true);
		cmds = cmds->next;
	}
	return (false);
}

t_hd_list *run_heredocs(t_cmd_list *cmds)
{
	t_hd_list	*head;
	int			fd;

	head = NULL;
	signals_setup(IGNORE);
	while (cmds)
	{
		if (cmds->content.heredoc_delim)
		{
			fd = handle_heredoc(&cmds->content);
			if (fd == -1 || !append_heredoc(&head, fd))
			{
				hd_lst_free(head);
				return (NULL);
			}
		}
		cmds = cmds->next;
	}
	return (head);
}
