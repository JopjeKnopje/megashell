/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:02:40 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/10 17:03:10 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	**search_in_path(char **envp, char *cmd)
{
	int		i;
	int		dup_cmd_index;
	int		envp_len;
	char	**dup_cmd;

	i = 0;
	dup_cmd_index = 0;
	envp_len = ft_strlen(envp[i]);
	dup_cmd = (char **)malloc(sizeof(char *) * (envp_len + 1));
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], cmd, ft_strlen(cmd)) == 0))
		{
			dup_cmd[dup_cmd_index] = ft_strdup(envp[i] + ft_strlen(cmd));
			dup_cmd_index++;
		}
		i++;
	}
	dup_cmd[dup_cmd_index] = NULL;
	return (dup_cmd);
}