/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 02:54:41 by joppe             #+#    #+#             */
/*   Updated: 2023/12/22 14:56:46 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include "heredoc.h"
#include "execute.h"
#include "input.h"
#include <asm-generic/errno-base.h>
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static int32_t	run_command(t_meta *meta, t_cmd_frame *cmd)
{
	t_builtin	is_builtin;
	char		*cmd_in_path;
	int32_t 	status;

	if (!cmd->argv)
		return (true);
	is_builtin = get_builtin(cmd->argv[0]);
	if (is_builtin)
		return (run_builtin(is_builtin, meta, cmd));
	status = get_runnable_path(meta, cmd->argv[0], &cmd_in_path);
	if (!status)
	{
		if (execve(cmd_in_path, cmd->argv, meta->envp) == -1)
		{
			perror("Megashell");
			return (INTERNAL_FAILURE);
		}
	}
	return (status);
}

static int	child_proc(t_meta *meta, t_cmd_list *cmd, t_hd_list **heredocs)
{
	int32_t	status;

	if (cmd->prev)
	{
		if (dup2(cmd->prev->pipe[PIPE_READ], STDIN_FILENO) == -1)
			return (errno);
		close(cmd->prev->pipe[PIPE_READ]);
		close(cmd->prev->pipe[PIPE_WRITE]);
	}
	if (cmd->next)
	{
		close(cmd->pipe[PIPE_READ]);
		if (dup2(cmd->pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			return (errno);
		close(cmd->pipe[PIPE_WRITE]);
	}
	set_signal_mode(CHILD);
	if (!redirections(&cmd->content, heredocs))
		status = 1;
	else
		status = run_command(meta, &cmd->content);
	if (status)
		perror("megashell");
	return (status);
}

bool	pipeline_node(t_meta *meta, t_cmd_list *cmd, t_hd_list **heredocs)
{
	if (cmd->next && pipe(cmd->pipe) == -1)
	{
		print_error(get_error_name(ERROR_PIPE));
		return (false);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		print_error(get_error_name(ERROR_FORK));
		return (false);
	}
	if (!cmd->pid)
	{
		if (!set_signal_mode(CHILD))
			exit(EXIT_FAILURE);
		exit(child_proc(meta, cmd, heredocs));
	}
	if (cmd->prev)
	{
		close(cmd->prev->pipe[PIPE_READ]);
		close(cmd->prev->pipe[PIPE_WRITE]);
	}
	return (true);
}

static int	pipeline_wait(t_cmd_list *cmds)
{
	int		status;

	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		cmds = cmds->next;
	}
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (WEXITSTATUS(status));
}

int	pipeline_start(t_meta *meta, t_cmd_list *cmds)
{
	t_hd_list			*heredoc_pipes;
	t_cmd_list *const	cmds_head = cmds;
	int					last_exit;

	heredoc_pipes = run_heredocs(cmds);
	if (contains_heredoc(cmds))
	{
		if (!heredoc_pipes)
			return (INTERNAL_FAILURE);
		last_exit = get_heredoc_exit_status(heredoc_pipes);
		if (last_exit)
		{
			hd_lst_free(heredoc_pipes);
			return (last_exit);
		}
	}
	if (!run_multiple_cmds(meta, cmds, cmds_head, heredoc_pipes))
		return (INTERNAL_FAILURE);
	last_exit = pipeline_wait(cmds_head);
	hd_lst_free(heredoc_pipes);
	printf("last_exit [%d]\n", last_exit);
	return (last_exit);
}
