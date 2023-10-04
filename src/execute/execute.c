/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 18:17:57 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "redirections.h"
#include "execute.h"
#include "megashell.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

// children_spawn: checks whether command has access
// if so it executes it and changes the stdin and stdout

bool	run_command(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	if (!cmds->content.argv)
		return (false);
	is_builtin = get_builtin(cmds->content.argv[0]);
	if (is_builtin)
	{
		return (run_builtin(is_builtin, meta, cmds));
	}
	char *cmd_in_path = access_possible(meta, cmds->content.argv[0]);
	if (cmd_in_path)
	{
		if (execve(cmd_in_path, cmds->content.argv, meta->envp) == -1)
		{
			print_error(get_error_name(ERROR_ACCESS));
			return (false);
		}
		return (true);
	}
	return (false);
}

// checks whether there is a next command, if so then
// the function will first pipe and then fork
// it enters the child processs if pid = 0


bool	start_pipe(t_meta *meta, t_cmd_list *cmds)
{
	pid_t 	pid;
	int		status;

	while (cmds)
	{
		if (cmds->next && pipe(cmds->pipe) == -1)
		{
			print_error(get_error_name(ERROR_PIPE));
			return (false);
		}
		pid = fork();
		if (pid == -1) /* fork returns -1 in case of error */
		{
			print_error(get_error_name(ERROR_FORK));
			return (false);
		}
		if (pid == 0) /* fork returns 0 for child process */
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
			printf("check\n");
			redirections(&cmds->content);
			if (!run_command(meta, cmds))
				exit(123);
			exit(EXIT_SUCCESS);
		}
		if (cmds->prev)
		{
			close(cmds->prev->pipe[PIPE_READ]);
			close(cmds->prev->pipe[PIPE_WRITE]);
		}
		cmds = cmds->next;
	}
	waitpid(pid, &status, 0);
	if (!WIFEXITED(status))
		fprintf(stderr, "Error child exited weirdly\n");
	printf("last exitcode: %d\n", WEXITSTATUS(status));
	return true;
}


bool	execution(t_meta *meta, t_cmd_list *cmds)
{
	// TODO: Only run single builtin by itself (can't really pipe `cd` effectively).
	return start_pipe(meta, cmds);
}
