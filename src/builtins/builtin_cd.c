/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/15 13:22:51 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// If no directory operand is given and the HOME environment variable is set
// to a non-empty value, the cd utility shall behave as if the directory named
// in the HOME environment variable was specified as the directory operand.

bool	builtin_run_cd(t_exec *execute, t_cmd_list *cmds)
{
	char		cwd[PATH_MAX];
	char		*tmp_home;
	int			path_len;

	printf("%s\n", cmds->next->action[0]);
	path_len = ft_strlen(cmds->action[1]);
	if (!cmds->action[1])
	{
		tmp_home = execute->envp("HOME"); /* HOME from my own envp*/
		if (!tmp_home)
			return (false);
		chdir(tmp_home);
	}
	if (strncmp(cmds->action[1], "..", path_len) == 0
		|| strncmp(cmds->action[1], "../", path_len) == 0)
		chdir("../");
	getcwd(cwd, sizeof(cwd));
	printf("Current working dir: %s\n", cwd);
	return (true);
}
