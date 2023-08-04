/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/05 00:46:34 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	dup_stdin(int file)
{
	if (dup2(file, STDIN_FILENO) == -1)
	{
		close (file);
		return (print_error(get_error_name(ERROR_DUP2)));
	}
	close(file);
	return (0);
}

int	dup_stdout(int file)
{
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		close (file);
		return (print_error(get_error_name(ERROR_DUP2)));
	}
	close(file);
	return (0);
}

