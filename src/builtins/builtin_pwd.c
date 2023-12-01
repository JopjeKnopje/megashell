/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:43:52 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/01 15:57:44 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "plarser.h"
#include "utils.h"

int	builtin_run_pwd(t_meta *meta, t_cmd_frame *cmd)
{
	char	cwd[PATH_MAX];
	char	**path;
	int		i;

	(void) meta;
	(void) cmd;
	i = 0;
	ft_bzero(&cwd, PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		path = search_in_path(meta->envp, "PWD=");
		while (path[i])
		{
			printf("%s\n", path[i]);
			i++;
		}
	}
	return (0);
}
