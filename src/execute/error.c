/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:19:02 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/21 22:16:00 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*get_error_name(t_error er)
{
	static char	*str[] = {\
		[ERROR_ARGUMENTS] = "Invalid Amount of Arguments", \
		[ERROR_PATH] = "Path Allocation Failure", \
		[ERROR_FIND_PATH] = "Path not Found", \
		[ERROR_PIPE] = "Pipe Error", \
		[ERROR_FORK] = "Fork Error", \
		[ERROR_DUP2] = "Duplication Error", \
		[ERROR_ACCESS] = "Access Failure", \
		[ERROR_ALLOC] = "Allocation Error", \
		[ERROR_DOT] = ".: filename argument required", \
		[ERROR_LEXER] = "Lexer failed\n"};

	return (str[er]);
}

int	print_error(char *str)
{
	write (STDERR_FILENO, "megashell: ", ft_strlen("megashell: "));
	write (STDERR_FILENO, str, ft_strlen(str));
	write (STDERR_FILENO, "\n", 2);
	return (EXIT_FAILURE);
}
