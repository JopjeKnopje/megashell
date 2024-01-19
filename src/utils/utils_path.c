/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:02:40 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/19 16:08:53 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "libft.h"
#include "plarser.h"

static void	iterate(char **envp, char *cmd, char **dup_cmd, int *dup_cmd_index)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], cmd, ft_strlen(cmd)) == 0))
		{
			dup_cmd[*dup_cmd_index] = ft_strdup(envp[i] + ft_strlen(cmd));
			if (!dup_cmd[*dup_cmd_index])
			{
				free(dup_cmd);
				break ;
			}
			(*dup_cmd_index)++;
		}
		i++;
	}
}

char	**search_in_env(char **envp, char *cmd)
{
	int		dup_cmd_index;
	char	**dup_cmd;

	if (!envp || !*envp)
		return (NULL);
	dup_cmd_index = 0;
	dup_cmd = (char **)malloc(sizeof(char *) * (ft_strlen(envp[0]) + 1));
	if (!dup_cmd)
		return (NULL);
	iterate(envp, cmd, dup_cmd, &dup_cmd_index);
	if (dup_cmd_index == 0)
	{
		free(dup_cmd);
		return (NULL);
	}
	dup_cmd[dup_cmd_index] = NULL;
	return (dup_cmd);
}
