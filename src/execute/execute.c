/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/18 16:52:43 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "megashell.h"

// children_spawn: checks whether command has access
// if so it executes it and changes the stdin and stdout

void	children_spawn(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	redirects(cmds);
	is_builtin = get_builtin(cmds->content.argv[0]);
	// printf("%s\n", BUILTINS_NAME[is_builtin]);
	if (is_builtin != BUILTIN_INVALID)
	{
		run_builtin(is_builtin, meta, cmds);
		return ;
	}
	else if (find_access(meta, cmds) == false)
	{
		print_error(get_error_name(ERROR_ACCESS));
		return ;
	}
	dup_io(&meta->execute, cmds);
}

// checks whether there is a next command, if so then
// the function will first pipe and then fork
// it enters the child processs if pid = 0

void	start_pipe(t_meta *meta, t_cmd_list *cmds)
{
	t_exec *execute = &meta->execute;
	int	status;

	while (cmds)
	{
		if (pipe(execute->io_file) == -1)
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
			children_spawn(meta, cmds);
		else
		{
			close(execute->io_file[IN_READ]); /* close fds in main process */
			close(execute->io_file[OUT_WRITE]);
		}
		cmds = cmds->next;
	}
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
	if ((cmds->next == NULL && get_builtin(cmds->content.argv[0])
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
