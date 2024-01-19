/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/19 18:18:49 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "megashell.h"
#include "utils.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	is_a_directory(char *cmd)
{
	struct stat	stat_of_cmd;

	if (stat(cmd, &stat_of_cmd) != 0)
		return (false);
	if (S_ISDIR(stat_of_cmd.st_mode))
		return (true);
	return (false);
}

static bool	is_file_path(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

static char	*find_executable_in_path(char **split_path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], cmd);
		if (!tmp)
			return (NULL);
		if (!access(tmp, F_OK | X_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

bool	is_path_set(t_meta *meta)
{
	bool	status;
	char	**s;

	s = search_in_env(meta->envp, "PATH=");
	if (s)
	{
		free_2d(s);
		status = true;
	}
	else
		status = false;
	return (status);
}

int32_t	get_runnable_path(t_meta *meta, char *cmd, char **runnable_cmd)
{
	if (cmd[0] == '.' && !cmd[1])
		return (2);
	if (is_file_path(cmd))
	{
		if (is_a_directory(cmd) && open(cmd, O_WRONLY) == -1)
			return (126);
		if (access(cmd, F_OK))
			return (127);
		if (access(cmd, X_OK))
			return (126);
		*runnable_cmd = cmd;
		return (0);
	}
	else if (!is_path_set(meta))
		return ((void) access(" ", F_OK), (127));
	else
	{
		*runnable_cmd = find_executable_in_path(meta->execute.split_path, cmd);
		if (!(*runnable_cmd))
			return (127);
		return (0);
	}
	return (INTERNAL_FAILURE);
}
