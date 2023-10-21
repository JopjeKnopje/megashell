/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:26:21 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/10 16:20:02 by ivan-mel         ###   ########.fr       */
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
	close(file);
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
	close(file);
	return (true);
}
