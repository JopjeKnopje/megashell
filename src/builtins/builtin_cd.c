/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/14 18:00:13 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	builtin_run_cd(t_exec *execute, t_cmd_list *cmds)
{
	char		cwd[PATH_MAX];

	printf("%s\n", cmds->action[1]);
	chdir(cmds->action[1]);
	// chdir("/Users/ivan-mel/Documents/Projects");
	getcwd(cwd, sizeof(cwd));
	printf("Current working dir: %s\n", cwd);
	return (true);
}
