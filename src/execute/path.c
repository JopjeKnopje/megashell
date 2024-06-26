/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:34:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/22 23:57:17 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "megashell.h"
#include "utils.h"
#include <stdio.h>

char	*find_path(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			return (envp[index] + 5);
		index++;
	}
	return (NULL);
}

char	**split_path(char *path)
{
	char	**path2;

	if (!path)
		return (NULL);
	path2 = ft_split(path, ':');
	if (!path2)
		return (NULL);
	return (path2);
}

// is het path of command -> zet in struct
// als het path is hoef je geen path aan toe te voegen (/)

char	**put_slash(char **path)
{
	char	*temp;
	int		index;

	index = 0;
	while (path[index])
	{
		temp = ft_strjoin(path[index], "/");
		if (!temp)
		{
			free_2d(path);
			return (NULL);
		}
		free(path[index]);
		path[index] = temp;
		index++;
	}
	return (path);
}

int	search_path(t_meta *meta, char **envp)
{
	char	*path;
	char	**path_after_split;

	meta->envp = duplicate_envp(envp);
	if (!meta->envp)
		return (1);
	path = find_path(meta->envp);
	if (!path)
		return (print_error(get_error_name(ERROR_FIND_PATH)));
	path_after_split = split_path(path);
	if (!path_after_split)
		return (print_error(get_error_name(ERROR_PATH)));
	meta->execute.split_path = put_slash(path_after_split);
	if (!meta->execute.split_path)
		return (print_error(get_error_name(ERROR_PATH)));
	return (0);
}
