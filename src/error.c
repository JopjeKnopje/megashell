/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:19:02 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/06 00:28:45 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

char	*get_error_name(t_error er)
{
	static char	*str[] = {\
		[ERROR_ARGUMENTS] = "Invalid Amount of Arguments", \
		[ERROR_PATH] = "Path Allocation Failure", \
		[ERROR_FIND_PATH] = "Path not Found", \
		[ERROR_PIPE] = "Pipe Error", \
		[ERROR_FORK] = "Fork Error", \
		[ERROR_DUP2] = "Duplication Error", \
		[ERROR_ACCESS] = "Access Failure"};

	return (str[er]);
}

int	print_error(char *str)
{
	write (STDERR_FILENO, str, ft_strlen(str));
	write (STDERR_FILENO, "\n", 2);
	return (EXIT_FAILURE);
}
