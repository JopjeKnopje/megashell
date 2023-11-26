/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 02:54:41 by joppe             #+#    #+#             */
/*   Updated: 2023/11/26 22:35:53 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include "heredoc.h"
#include "execute.h"
#include "input.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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

static int child_proc(t_meta *meta, t_cmd_list *cmd, t_hd_list **heredocs)
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

static bool pipeline_node(t_meta *meta, t_cmd_list *cmd, t_hd_list **heredocs)
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
	signals_setup(1);
	return (true);
}

// TODO: Test wether handle when the child segfaults n stuff.
static int pipeline_wait(t_cmd_list *cmds)
{
	int		status;

	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		cmds = cmds->next;
	}
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (WEXITSTATUS(status));
}

void set_lastexit_var(char **envp, int status)
{
	char *s = ft_itoa(status);
	if (!s)
		UNIMPLEMENTED("no mem prot");
	char *value = env_set_var(envp, LAST_EXIT_VAR, s);
	free(s);
	printf("value = [%s]\n", value);
}

bool	pipeline_start(t_meta *meta, t_cmd_list *cmds)
{
	t_hd_list	*heredoc_pipes;
	t_cmd_list	*cmds_head;
	int			last_exit;

	(void) last_exit;
	cmds_head = cmds;
	signals_setup(IGNORE);
	heredoc_pipes = run_heredocs(cmds);
	if (contains_heredoc(cmds) && !heredoc_pipes)
		return (false);
	while (cmds)
	{
		if (!pipeline_node(meta, cmds, &heredoc_pipes))
		{
			assert(1 && "pipeline_node failure\n");
		}
		cmds = cmds->next;
	}
	last_exit = pipeline_wait(cmds_head);
	hd_lst_free(heredoc_pipes);
	set_lastexit_var(meta->envp, last_exit);

	// g_signal_num = last_exit;
	signals_setup(MAIN);
	return (true);
}
