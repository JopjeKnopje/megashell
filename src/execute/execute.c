/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/24 00:04:48 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "megashell.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

// children_spawn: checks whether command has access
// if so it executes it and changes the stdin and stdout

void	children_spawn(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	redirects(cmds);

	is_builtin = get_builtin(cmds->content.argv[0]);
	if (is_builtin != BUILTIN_INVALID)
	{
		run_builtin(is_builtin, meta, cmds);
		return ;
	}

	char *cmd_in_path = access_possible(meta, cmds->content.argv[0]);
	if (cmd_in_path)
	{
		execve(cmd_in_path, cmds->content.argv, meta->envp);
		print_error(get_error_name(ERROR_ACCESS));
		return ;
	}
}

// checks whether there is a next command, if so then
// the function will first pipe and then fork
// it enters the child processs if pid = 0


void	start_pipe(t_meta *meta, t_cmd_list *cmds)
{
	t_exec	*execute;
	int		status;

	execute = &meta->execute;
	while (cmds)
	{
		if (cmds->next && pipe(cmds->pipe) == -1)
		{
			print_error(get_error_name(ERROR_PIPE));
			return ;
		}
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error */
		{
			print_error(get_error_name(ERROR_FORK));
			return ;
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
			children_spawn(meta, cmds);
			exit(69);
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
	// while (wait(NULL) != -1)
	// 	continue ;
}

void run_single_builtin(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	is_builtin = get_builtin(cmds->content.argv[0]);
	printf("%s\n", BUILTINS_NAME[is_builtin]);
	if (is_builtin != BUILTIN_INVALID)
	{
		run_builtin(is_builtin, meta, cmds);
		return ;
	}
}

void	run_single_command(t_meta *meta, t_cmd_list *cmds)
{
	const t_exec *execute = &meta->execute;
	meta->execute.pid = fork();
	if (execute->pid == -1)
	{
		print_error(get_error_name(ERROR_FORK));
		return ;
	}
	if (execute->pid == 0)
	{
		redirects(cmds);
		if (find_access(meta, cmds) == false)
		{
			print_error(get_error_name(ERROR_ACCESS));
			exit (EXIT_FAILURE);
		}
	}
	wait(NULL);
}

void	execution(t_meta *meta, t_cmd_list *cmds)
{
	t_cmd_list	*cmd_list;

	cmd_list = cmds;
	if ((cmds->next == NULL && get_builtin(cmds->content.argv[0])
			!= BUILTIN_INVALID))
	{
		printf("single builtin\n");	
		run_single_builtin(meta, cmds);
	}
	else if ((cmds->next == NULL && get_builtin(cmds->content.argv[0])
			== BUILTIN_INVALID))
	{
		printf("single command\n");
		run_single_command(meta, cmd_list);
	}
	if (cmds->next)
	{
		printf("starting pipe\n");	
		start_pipe(meta, cmd_list);
	}
}
