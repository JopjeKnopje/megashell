/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 02:54:41 by joppe             #+#    #+#             */
/*   Updated: 2023/12/11 16:00:40 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include "heredoc.h"
#include "execute.h"
#include "input.h"
#include "test_utils.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static bool	run_command(t_meta *meta, t_cmd_frame *cmd)
{
	t_builtin	is_builtin;
	char		*cmd_in_path;

	if (!cmd->argv)
		return (true);
	is_builtin = get_builtin(cmd->argv[0]);
	if (is_builtin)
		return (run_builtin(is_builtin, meta, cmd));
	cmd_in_path = access_possible(meta, cmd->argv[0]);
	if (cmd_in_path)
	{
		if (execve(cmd_in_path, cmd->argv, meta->envp) == -1)
		{
			print_error(get_error_name(ERROR_ACCESS));
			return (false);
		}
		return (true);
	}
	return (false);
}

static int	child_proc(t_meta *meta, t_cmd_list *cmd, t_hd_list **heredocs)
{
	if (cmd->prev)
	{
		if (dup2(cmd->prev->pipe[PIPE_READ], STDIN_FILENO) == -1)
			perror(strerror(errno));
		close(cmd->prev->pipe[PIPE_READ]);
		close(cmd->prev->pipe[PIPE_WRITE]);
	}
	if (cmd->next)
	{
		close(cmd->pipe[PIPE_READ]);
		if (dup2(cmd->pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			perror(strerror(errno));
		close(cmd->pipe[PIPE_WRITE]);
	}
	signals_setup(CHILD);
	redirections(&cmd->content, heredocs);
	return (!run_command(meta, &cmd->content));
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
		signals_setup(CHILD);
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
	{
		return (WTERMSIG(status) + 128);
	}
	else
	{
		return (WEXITSTATUS(status));
	}
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
			return (0);
		last_exit = get_heredoc_exit_status(heredoc_pipes);
		if (last_exit)
		{
			hd_lst_free(heredoc_pipes);
			return (last_exit);
		}
	}
	if (!run_multiple_cmds(meta, cmds, cmds_head, heredoc_pipes))
		return (-1);
	last_exit = pipeline_wait(cmds_head);
	hd_lst_free(heredoc_pipes);
	return (last_exit);
}
