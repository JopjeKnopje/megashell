/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 15:23:30 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "plarser.h"
#include "redirections.h"
#include "execute.h"
#include "megashell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

bool try_builtin(t_cmd_frame *cmd, t_meta *meta)
{
	t_builtin	is_builtin;
	is_builtin = get_builtin(cmd->argv[0]);
	if (is_builtin)
	{
		return run_builtin(is_builtin, meta, cmd);
	}
	return (false);
}

bool	run_command(t_meta *meta, t_cmd_frame *cmd)
{

	if (!cmd->argv)
		return false;

	try_builtin(cmd, meta);

	char *cmd_in_path = access_possible(meta, cmd->argv[0]);
	if (cmd_in_path)
	{
		execve(cmd_in_path, cmd->argv, meta->envp);
		print_error(get_error_name(ERROR_ACCESS));
		return false;
	}
	return true;
}

bool	start_pipeline(t_meta *meta, t_cmd_list *cmds)
{
	t_exec	*execute;
	int		status;

	execute = &meta->execute;
	while (cmds)
	{
		if (cmds->next && pipe(cmds->pipe) == -1)
		{
			print_error(get_error_name(ERROR_PIPE));
			return (false);
		}
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error */
		{
			print_error(get_error_name(ERROR_FORK));
			return (false);
		}
		if (execute->pid == 0) /* fork returns 0 for child process */
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
			// setup_io(cmds);
			if (run_command(meta, &cmds->content))
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		if (cmds->prev)
		{
			close(cmds->prev->pipe[PIPE_READ]);
			close(cmds->prev->pipe[PIPE_WRITE]);
		}
		if (!cmds->next)
		{
			close(cmds->pipe[PIPE_READ]);
			close(cmds->pipe[PIPE_WRITE]);
		}
		cmds = cmds->next;
	}
	waitpid(execute->pid, &status, 0);
	printf("last exitcode: %d\n", WEXITSTATUS(status));
	return (true);
}

void run_single_builtin(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;
	int			std_in;
	int			std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	is_builtin = get_builtin(cmds->content.argv[0]);
	printf("%s\n", BUILTINS_NAME[is_builtin]);
	setup_io(cmds);
	run_builtin(is_builtin, meta, cmds);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
}

bool	execute(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin is_builtin;

	if (cmds->content.argv)
		is_builtin = get_builtin(cmds->content.argv[0]);
	else 
		is_builtin = BUILTIN_INVALID;

	if (!cmds->next && is_builtin)
		return run_builtin(is_builtin, meta, cmds);
	return (start_pipeline(meta, cmds));
}
