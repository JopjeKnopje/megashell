/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/05 23:53:46 by iris             ###   ########.fr       */
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

char	*access_possible(t_exec *execute, char *list)
{
	int		i;
	char	*tmp;

	i = 0;
	while (execute->split_path[i])
	{
		tmp = ft_strjoin(execute->split_path[i], ft_strjoin("/", list));
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK | F_OK) == 0)
		{
			printf("cmd: %s\n", tmp);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}