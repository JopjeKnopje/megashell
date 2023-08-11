/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:26:21 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/11 16:19:17 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
