/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:43:52 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/26 13:55:07 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include "utils.h"

int	builtin_run_pwd(t_meta *meta, t_cmd_frame *cmd)
{
	char	cwd[PATH_MAX];
	char	**path;
	int		i;

	(void) cmd;
	(void) meta;
	path = NULL;
	i = 0;
	ft_bzero(&cwd, PATH_MAX);
	path = search_in_env(meta->envp, "PWD=");
	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
	free_2d(path);
	return (0);
}
