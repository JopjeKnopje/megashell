/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/02 00:30:54 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

static bool connect_pipe(t_exec *exec, t_cmd_list *cmds)
{
	if (!cmds->prev && cmds->next)
	{
		// redirect STDOUT -> PIPE_WRITE
		if (dup2(exec->io_file[PIPE_WRITE], STDOUT_FILENO) == -1)
		{
			perror(strerror(errno));
			return false;
		}
		if (close(exec->io_file[PIPE_READ]) == -1)
		{
			perror(strerror(errno));
			return false;
		}
	}
	if (cmds->prev && !cmds->next)
	{
		// redirect PIPE_READ -> STDIN
		if (dup2(exec->io_file[PIPE_READ], STDIN_FILENO) == -1)
		{
			printf("asd\n");
			perror(strerror(errno));
			return false;
		}
		if (close(exec->io_file[PIPE_WRITE]) == -1)
		{
			perror(strerror(errno));
			return false;
		}
	}
	return true;
}

// children_spawn: checks whether command has access
// if so it executes it and changes the stdin and stdout
void	children_spawn(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	// redirects();
	is_builtin = get_builtin(cmds->content.argv[0]);
	if (is_builtin != BUILTIN_INVALID)
	{
		run_builtin(is_builtin, meta, cmds);
		return ;
	}

	char *path = access_possible(meta, cmds->content.argv[0]);
	if (!path)
	{
		printf("[%s] is not runnable\n", path);
		return;
	}
	printf("running [%s]\n", path);

	// dup_io(&meta->execute, cmds);
	connect_pipe(&meta->execute, cmds);
	if (execve (path, cmds->content.argv, meta->envp) == -1)
		perror(strerror(errno));

}

// checks whether there is a next command, if so then
// the function will first pipe and then fork
// it enters the child processs if pid = 0

void	start_pipe(t_meta *meta, t_cmd_list *cmds)
{
	t_exec *execute = &meta->execute;
	int	status;

	if (pipe(execute->io_file) == -1)
	{
		print_error(get_error_name(ERROR_PIPE));
		return ;
	}
	while (cmds)
	{
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error */
		{
			print_error(get_error_name(ERROR_FORK));
			return ;
		}
		if (execute->pid == 0) /* fork returns 0 for child process */
		{
			children_spawn(meta, cmds);
			fprintf(stderr, "execve failed\n");
			exit(69);
		}
		cmds = cmds->next;
	}
	close(execute->io_file[IN_READ]); /* close fds in main process */
	close(execute->io_file[OUT_WRITE]);
	waitpid(execute->pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
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

	// heredoc?	
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
	else if (cmds->next)
	{
		printf("starting pipe\n");	
		start_pipe(meta, cmd_list);
	}
}
