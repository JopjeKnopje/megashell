/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                   :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:26:21 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/02 00:09:28 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//dup_stdin: duplicates the read side of the pipe to
// stdin, dup2 closes the STDIN side automatically but
// the file side still has to be closed.

bool	dup_stdin(int file)
{
	if (dup2(file, STDIN_FILENO) == -1)
	{
		close (file);
		return (false);
	}
	return (true);
}

//dup_stdout: duplicates the write side of the pipe to
// stdout, dup2 closes the STDOUT side automatically but
// the file side still has to be closed.

bool	dup_stdout(int file)
{
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		close (file);
		return (false);
	}
	return (true);
}

// @param execute: struct that contains execution info
// @param cmds: struct with linked list of commands

// dup_cmd: duplicates the read side of pipe to stdin
// and the write side of the pipe to stdout as long
// as it has a previous or next command.

void	dup_io(t_exec *execute, t_cmd_list *cmds)
{
	if (cmds->prev && dup_stdin(execute->io_file[IN_READ]) == false)
	{
		print_error(get_error_name(ERROR_DUP2));
	}
	else if (cmds->next && dup_stdout(execute->io_file[OUT_WRITE]) == false)
	{
		print_error(get_error_name(ERROR_DUP2));
	}
	else if (cmds->next == NULL && dup_stdout(execute->io_file[OUT_WRITE]) == false)
	{
		print_error(get_error_name(ERROR_DUP2));
	}
}
