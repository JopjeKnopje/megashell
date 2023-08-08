/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/08 17:43:06 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

// @param execute: struct that contains execution info
// @param cmds: struct with linked list of commands

// dup_cmd: duplicates the read side of pipe to stdin
// and the write side of the pipe to stdout as long as
// as it has a previous or next command.

void	dup_io(t_exec *execute, t_cmd_list *cmds)
{
	if (cmds->prev && dup_stdin(execute->pipes_fd[IN_READ]) == false)
		print_error(get_error_name(ERROR_DUP2));
	if (cmds->next && dup_stdout(execute->pipes_fd[OUT_WRITE]) == false)
		print_error(get_error_name(ERROR_DUP2));
}

// @param execute: struct that contains execution info
// @param cmds: struct with linked list of commands

// children_spawn: checks whether command has access
// if so it executes it and changes the stdin and stdout

void	children_spawn(t_exec *execute, t_cmd_list *cmds)
{
	redirects();
	// builtins();
	if (find_access(execute, cmds) == false)
		print_error(get_error_name(ERROR_ACCESS));
	dup_cmd(execute, cmds);
}

// @param execute: struct that contains execution info
// @param cmds: struct with linked list of commands

// checks whether there is a next command, if so then
// the function will first pipe and then fork
// it enters the child processs if pid = 0

void	start_pipe(t_exec *execute, t_cmd_list *cmds)
{
	while (cmds->next)
	{
		if (pipe(execute->pipes_fd) == -1)
		{
			print_error(get_error_name(ERROR_PIPE));
			return ;
		}
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error*/
		{
			print_error(get_error_name(ERROR_FORK));
			return ;
		}
		if (execute->pid == 0) /* fork returns 0 for child process */
			children_spawn(execute, cmds);
		else
		{
			close(execute->pipes_fd[IN_READ]);/* close fds in main process */
			close(execute->pipes_fd[OUT_WRITE]);
		}
		cmds = cmds->next;
	}
}

// void	single_child()
// {
	
// }

void	execution(t_exec *execute, t_cmd_list *list)
{
	int			pipes_fd[2];
	int			prev_pipe;
	int			status;
	t_cmd_list	*cmd_list;

	cmd_list = list;
	// heredoc?	
//	if (cmds->next == 0) /* && is_it_builtin(cmds->action[i]) == true) */
//		single_child(); /*  afhankelijk van builtin */
	if (cmd_list->next)
		start_pipe(execute, cmd_list);
}
