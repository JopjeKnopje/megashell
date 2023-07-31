/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:19:02 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/07/31 14:00:34 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

char	*get_error_name(t_error er)
{
	static char	*str[] = {\
		[ERROR_ARGUMENTS] = "Invalid Amount of Arguments", \
		[ERROR_PATH] = "Path Allocation Failure"};

	return (str[er]);
}

int	print_error(char *str)
{
	write (STDERR_FILENO, str, ft_strlen(str));
	write (STDERR_FILENO, "\n", 2);
	return (EXIT_FAILURE);
}
