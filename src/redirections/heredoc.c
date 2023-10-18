/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:06:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/18 17:00:19 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "execute.h"
#include "plarser.h"
#include "libft.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

uint8_t	read_from_heredoc(char *close_line, int pipe_fd)
{
	char	*line;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, close_line, ft_strlen(close_line) + 1))
		{
			free(line);
			printf("same\n");;
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
	int	pipe_fd[2];
	// int	*pipe_fd = ft_calloc(2, sizeof(int));
	int	pid;
	int	status;
	uint8_t	child_exit_code;

	if (pipe(pipe_fd) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		close (pipe_fd[PIPE_READ]);
		child_exit_code = read_from_heredoc(f->heredoc_delim, pipe_fd[PIPE_WRITE]);
		close (pipe_fd[PIPE_WRITE]);
		exit(child_exit_code);
	}
	close(pipe_fd[PIPE_WRITE]);
	waitpid(pid, &status, 0);
	child_exit_code = WEXITSTATUS(status);
	dprintf(STDERR_FILENO, "child_exit %d\n", child_exit_code);
	return (pipe_fd[PIPE_READ]);
}

t_hd_list *run_heredocs(t_cmd_list *cmds)
{
	t_hd_list *head = NULL;
	size_t i = 0;

	while (cmds)
	{
		if (cmds->content.heredoc_delim)
		{
			int fd = handle_heredoc(&cmds->content);
			if (fd == -1)
			{
				// TODO Handle error.
			}
			i++;
			hd_lstadd_back(&head, hd_lstnew(fd));
		}
		cmds = cmds->next;
	}
	return (head);
}
