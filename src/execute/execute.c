/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/17 13:42:48 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "plarser.h"
#include "redirections.h"
#include "execute.h"
#include "megashell.h"
#include "utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

bool	run_command(t_meta *meta, t_cmd_frame *cmd)
{
	t_builtin	is_builtin;
	char		*cmd_in_path;

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

int	start_childprocess(t_meta *meta, t_cmd_list *cmds)
{
	if (cmds->prev)
	{
		if (dup2(cmds->prev->pipe[PIPE_READ], STDIN_FILENO) == -1)
			perror(strerror(errno));
		close(cmds->prev->pipe[PIPE_READ]);
		close(cmds->prev->pipe[PIPE_WRITE]);
	}
	if (cmds->next)
	{
		close(cmds->pipe[PIPE_READ]);
		if (dup2(cmds->pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			perror(strerror(errno));
		close(cmds->pipe[PIPE_WRITE]);
	}
	redirections(&cmds->content);
	if (!run_command(meta, &cmds->content))
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

bool	start_pipeline(t_meta *meta, t_cmd_list *cmds)
{
	pid_t	pid;
	int		status;

	while (cmds)
	{
		if (cmds->next && pipe(cmds->pipe) == -1)
			return (print_error(get_error_name(ERROR_PIPE)), false);
		pid = fork();
		if (pid == -1)
			return (print_error(get_error_name(ERROR_FORK)), false);
		if (pid == 0)
			start_childprocess(meta, cmds);
		if (cmds->prev)
		{
			close(cmds->prev->pipe[PIPE_READ]);
			close(cmds->prev->pipe[PIPE_WRITE]);
		}
		cmds = cmds->next;
	}
	waitpid(pid, &status, 0);
	return (true);
}

bool	execute(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	is_builtin = get_builtin(cmds->content.argv[0]);
	if (is_builtin)
		return (run_builtin(is_builtin, meta, &cmds->content));
	else
		return (start_pipeline(meta, cmds));
	return (false);
}
